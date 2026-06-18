import { useEffect, useState, useCallback } from "react";
import { Search, CalendarDays, MapPin, X, Check, Clock, Ban } from "lucide-react";
import { reservaService, imoveisService, usuarioService, type Reserva, type Imovel } from "../services/api";
import { useStore } from "../app/store";

function reservaCode(id: number): string {
  return "RES-" + id.toString(36).toUpperCase().padStart(3, "0");
}
function abbrevName(name: string): string {
  const parts = name.trim().split(/\s+/);
  if (parts.length <= 1 || name.length <= 18) return name;
  return parts[0] + " " + parts.slice(1).map((p) => p[0] + ".").join(" ");
}

function fmt(v: number) {
  return v.toLocaleString("pt-BR", { style: "currency", currency: "BRL", maximumFractionDigits: 0 });
}

function statusInfo(s: Reserva["status"]) {
  if (s === "CONFIRMADA") return { label: "Confirmada", cls: "badge-green", icon: <Check size={11} /> };
  if (s === "CANCELADA") return { label: "Cancelada", cls: "badge-red", icon: <Ban size={11} /> };
  return { label: "Pendente", cls: "badge-amber", icon: <Clock size={11} /> };
}

type StatusFilter = "ALL" | Reserva["status"];

export default function HostReservations() {
  const { user } = useStore();
  const [reservations, setReservations] = useState<Reserva[]>([]);
  const [properties, setProperties] = useState<Record<number, Imovel>>({});
  const [loading, setLoading] = useState(true);
  const [searchInput, setSearchInput] = useState("");
  const [search, setSearch] = useState("");
  const [statusFilter, setStatusFilter] = useState<StatusFilter>("ALL");
  const [periodoDe, setPeriodoDe] = useState("");
  const [periodoAte, setPeriodoAte] = useState("");
  const [selected, setSelected] = useState<Reserva | null>(null);
  const [hospedeMap, setHospedeMap] = useState<Record<number, string>>({});
  const [confirming, setConfirming] = useState<number | null>(null);
  const [cancelling, setCancelling] = useState<number | null>(null);

  useEffect(() => {
    const t = setTimeout(() => setSearch(searchInput), 400);
    return () => clearTimeout(t);
  }, [searchInput]);

  const fetch = useCallback(async () => {
    if (!user) return;
    setLoading(true);
    try {
      const params: Parameters<typeof reservaService.getAll>[0] = {
        idUsuario: user.idUsuario,
        papel: "anfitriao",
      };
      if (statusFilter !== "ALL") params.status = statusFilter;
      if (search.trim()) params.busca = search.trim();
      if (periodoDe) params.periodoDe = periodoDe;
      if (periodoAte) params.periodoAte = periodoAte;
      const res = await reservaService.getAll(params);
      setReservations(res);

      const ids = [...new Set(res.map((r) => r.idImovel))];
      const map: Record<number, Imovel> = {};
      const [, users] = await Promise.all([
        Promise.all(ids.map((id) => imoveisService.getById(id).then((p) => { map[id] = p; }).catch(() => {}))),
        usuarioService.getAll(),
      ]);
      setProperties(map);
      setHospedeMap(Object.fromEntries(users.map((u) => [u.idUsuario, u.nome])));
    } finally {
      setLoading(false);
    }
  }, [user, statusFilter, search, periodoDe, periodoAte]);

  useEffect(() => { fetch(); }, [fetch]);

  const handleConfirm = async (r: Reserva) => {
    setConfirming(r.idReserva);
    try {
      const updated = await reservaService.confirm(r.idReserva, r.formaPagamento || "PIX");
      setReservations((prev) => prev.map((res) => res.idReserva === r.idReserva ? updated : res));
      if (selected?.idReserva === r.idReserva) setSelected(updated);
    } catch (e) {
      alert(e instanceof Error ? e.message : "Erro ao confirmar");
    } finally {
      setConfirming(null);
    }
  };

  const handleCancel = async (r: Reserva) => {
    if (!confirm("Cancelar esta reserva?")) return;
    setCancelling(r.idReserva);
    try {
      await reservaService.update(r.idReserva, { status: "CANCELADA" });
      setReservations((prev) => prev.map((res) => res.idReserva === r.idReserva ? { ...res, status: "CANCELADA" } : res));
      if (selected?.idReserva === r.idReserva) setSelected((s) => s ? { ...s, status: "CANCELADA" } : null);
    } catch (e) {
      alert(e instanceof Error ? e.message : "Erro ao cancelar");
    } finally {
      setCancelling(null);
    }
  };

  return (
    <div style={{ display: "flex", height: "100vh", overflow: "hidden" }}>
      <div style={{ flex: 1, display: "flex", flexDirection: "column", overflow: "hidden" }}>
        <div style={{ padding: "24px 28px 0", flexShrink: 0 }}>
          <h1 style={{ fontSize: 22, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.04em", margin: "0 0 4px" }}>
            Reservas Recebidas
          </h1>
          <p style={{ fontSize: 13, color: "var(--ink-3)", margin: "0 0 20px" }}>
            {reservations.length} reserva{reservations.length !== 1 ? "s" : ""} nos seus imóveis
          </p>

          <div style={{ display: "flex", gap: 10, marginBottom: 16, flexWrap: "wrap" }}>
            <div style={{ position: "relative", flex: 1, minWidth: 200 }}>
              <Search size={14} style={{ position: "absolute", left: 12, top: "50%", transform: "translateY(-50%)", color: "var(--ink-4)", pointerEvents: "none" }} />
              <input className="field-input" style={{ paddingLeft: 34 }} placeholder="Buscar por data, pagamento..." value={searchInput} onChange={(e) => setSearchInput(e.target.value)} />
            </div>
            <input className="field-input" type="date" value={periodoDe} onChange={(e) => setPeriodoDe(e.target.value)} title="De" style={{ width: 148 }} />
            <input className="field-input" type="date" value={periodoAte} onChange={(e) => setPeriodoAte(e.target.value)} title="Até" style={{ width: 148 }} />
            {(["ALL", "PENDENTE", "CONFIRMADA", "CANCELADA"] as StatusFilter[]).map((s) => (
              <button key={s} onClick={() => setStatusFilter(s)}
                style={{
                  padding: "8px 14px", borderRadius: "var(--radius-sm)",
                  border: `1.5px solid ${statusFilter === s ? "var(--accent)" : "var(--border)"}`,
                  background: statusFilter === s ? "var(--accent-tint)" : "var(--surface)",
                  color: statusFilter === s ? "var(--accent)" : "var(--ink-3)",
                  fontSize: 12, fontWeight: 600, transition: "all 120ms ease",
                }}>
                {s === "ALL" ? "Todas" : s === "CONFIRMADA" ? "Confirmadas" : s === "PENDENTE" ? "Pendentes" : "Canceladas"}
              </button>
            ))}
          </div>
        </div>

        <div style={{ flex: 1, overflowY: "auto", padding: "0 28px 28px" }}>
          {loading ? (
            <div style={{ display: "flex", flexDirection: "column", gap: 10, paddingTop: 12 }}>
              {[1, 2, 3].map((i) => <div key={i} style={{ height: 96, borderRadius: "var(--radius-lg)", background: "var(--canvas)" }} />)}
            </div>
          ) : reservations.length === 0 ? (
            <div style={{ paddingTop: 48, textAlign: "center" }}>
              <CalendarDays size={40} style={{ color: "var(--ink-5)", margin: "0 auto 12px" }} />
              <p style={{ fontSize: 14, color: "var(--ink-3)", margin: 0 }}>
                Nenhuma reserva encontrada.
              </p>
            </div>
          ) : (
            <div style={{ display: "flex", flexDirection: "column", gap: 8, paddingTop: 12 }}>
              {reservations.map((r) => {
                const prop = properties[r.idImovel];
                const { label, cls } = statusInfo(r.status);
                const isActive = selected?.idReserva === r.idReserva;
                return (
                  <div key={r.idReserva} className="card" onClick={() => setSelected(isActive ? null : r)}
                    style={{
                      padding: "14px 18px", display: "flex", gap: 14, cursor: "pointer",
                      border: isActive ? "1.5px solid var(--accent)" : "1px solid var(--border)",
                      transition: "all 140ms ease",
                    }}>
                    {prop?.fotos?.[0] ? (
                      <img src={prop.fotos[0]} alt="" style={{ width: 64, height: 64, borderRadius: "var(--radius-sm)", objectFit: "cover", flexShrink: 0 }} />
                    ) : (
                      <div style={{ width: 64, height: 64, borderRadius: "var(--radius-sm)", background: "var(--canvas)", display: "flex", alignItems: "center", justifyContent: "center", flexShrink: 0 }}>
                        <MapPin size={20} style={{ color: "var(--ink-5)" }} />
                      </div>
                    )}
                    <div style={{ flex: 1, minWidth: 0 }}>
                      <div style={{ fontSize: 13, fontWeight: 700, color: "var(--ink)", marginBottom: 2, overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap" }}>
                        {prop?.titulo ?? `Imóvel #${r.idImovel}`}
                      </div>
                      <div style={{ fontSize: 11, color: "var(--ink-3)", marginBottom: 4 }}>
                        {abbrevName(hospedeMap[r.idHospede] ?? "Hóspede #" + r.idHospede)} · {r.dataInicio} → {r.dataFim}
                      </div>
                      {r.status === "PENDENTE" && (
                        <button onClick={(e) => { e.stopPropagation(); handleConfirm(r); }}
                          disabled={confirming === r.idReserva}
                          style={{
                            padding: "4px 12px", borderRadius: "var(--radius-sm)", border: "none",
                            background: "var(--green)", color: "#fff", fontSize: 11, fontWeight: 600,
                          }}>
                          {confirming === r.idReserva ? "Confirmando..." : "Confirmar"}
                        </button>
                      )}
                    </div>
                    <div style={{ display: "flex", flexDirection: "column", alignItems: "flex-end", gap: 6, flexShrink: 0 }}>
                      <span className={`badge ${cls}`}>{label}</span>
                      <span style={{ fontSize: 14, fontWeight: 700, color: "var(--ink)" }}>{fmt(r.valorTotal)}</span>
                    </div>
                  </div>
                );
              })}
            </div>
          )}
        </div>
      </div>

      {selected && (
        <div className="anim-slide-right"
          style={{
            width: 300, minWidth: 300, height: "100vh", overflowY: "auto",
            borderLeft: "1px solid var(--border)", background: "var(--surface)",
            display: "flex", flexDirection: "column",
          }}>
          <div style={{ padding: "20px 20px 0", display: "flex", alignItems: "center", justifyContent: "space-between", flexShrink: 0 }}>
            <h3 style={{ fontSize: 15, fontWeight: 700, color: "var(--ink)", margin: 0 }}>
              {reservaCode(selected.idReserva)}
            </h3>
            <button onClick={() => setSelected(null)} style={{ background: "none", border: "none", color: "var(--ink-3)", display: "flex", padding: 4 }}>
              <X size={18} />
            </button>
          </div>
          <div style={{ padding: "16px 20px", flex: 1 }}>
            <div className="card" style={{ padding: "14px 16px", marginBottom: 12 }}>
              {[
                ["Hóspede", abbrevName(hospedeMap[selected.idHospede] ?? "#" + selected.idHospede)],
                ["Imóvel", properties[selected.idImovel]?.titulo ?? `#${selected.idImovel}`],
                ["Check-in", selected.dataInicio],
                ["Check-out", selected.dataFim],
                ["Pagamento", selected.formaPagamento || "—"],
                ["Total", fmt(selected.valorTotal)],
              ].map(([label, val], i, arr) => (
                <div key={i} style={{
                  display: "flex", justifyContent: "space-between", paddingBottom: i < arr.length - 1 ? 10 : 0,
                  marginBottom: i < arr.length - 1 ? 10 : 0, borderBottom: i < arr.length - 1 ? "1px solid var(--border)" : "none",
                }}>
                  <span style={{ fontSize: 12, color: "var(--ink-3)" }}>{label}</span>
                  <span style={{ fontSize: 12, fontWeight: 600, color: "var(--ink-2)", maxWidth: 160, textAlign: "right", overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap" }}>{val}</span>
                </div>
              ))}
            </div>
            {selected.status === "PENDENTE" && (
              <div style={{ display: "flex", flexDirection: "column", gap: 8 }}>
                <button onClick={() => handleConfirm(selected)} disabled={confirming === selected.idReserva}
                  style={{ padding: "10px", borderRadius: "var(--radius-md)", border: "none", background: "var(--green)", color: "#fff", fontWeight: 600, fontSize: 13 }}>
                  {confirming === selected.idReserva ? "Confirmando..." : "✓ Confirmar reserva"}
                </button>
                <button onClick={() => handleCancel(selected)} disabled={cancelling === selected.idReserva}
                  style={{ padding: "10px", borderRadius: "var(--radius-md)", border: "1.5px solid var(--red)", background: "var(--red-tint)", color: "var(--red)", fontWeight: 600, fontSize: 13 }}>
                  {cancelling === selected.idReserva ? "Cancelando..." : "Cancelar"}
                </button>
              </div>
            )}
          </div>
        </div>
      )}
    </div>
  );
}
