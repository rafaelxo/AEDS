import { useEffect, useState, useCallback } from "react";
import { useNavigate } from "react-router-dom";
import { Search, CalendarDays, X, AlertCircle, MapPin } from "lucide-react";
import { reservaService, imoveisService, type Reserva, type Imovel } from "../services/api";

function reservaCode(id: number): string {
  return "RES-" + id.toString(36).toUpperCase().padStart(3, "0");
}
import { useStore } from "../app/store";

function fmt(v: number) {
  return v.toLocaleString("pt-BR", { style: "currency", currency: "BRL", maximumFractionDigits: 0 });
}

function statusInfo(s: Reserva["status"]) {
  if (s === "CONFIRMADA") return { label: "Confirmada", cls: "badge-green" };
  if (s === "CANCELADA") return { label: "Cancelada", cls: "badge-red" };
  return { label: "Pendente", cls: "badge-amber" };
}

type StatusFilter = "ALL" | Reserva["status"];

export default function GuestReservations() {
  const { user, openDetail } = useStore();
  const navigate = useNavigate();
  const [reservations, setReservations] = useState<Reserva[]>([]);
  const [properties, setProperties] = useState<Record<number, Imovel>>({});
  const [loading, setLoading] = useState(true);
  const [searchInput, setSearchInput] = useState("");
  const [search, setSearch] = useState("");
  const [statusFilter, setStatusFilter] = useState<StatusFilter>("ALL");
  const [periodoDe, setPeriodoDe] = useState("");
  const [periodoAte, setPeriodoAte] = useState("");
  const [cancelling, setCancelling] = useState<number | null>(null);
  const [selected, setSelected] = useState<Reserva | null>(null);

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
        papel: "hospede",
      };
      if (statusFilter !== "ALL") params.status = statusFilter;
      if (search.trim()) params.busca = search.trim();
      if (periodoDe) params.periodoDe = periodoDe;
      if (periodoAte) params.periodoAte = periodoAte;
      const res = await reservaService.getAll(params);
      setReservations(res);

      const ids = [...new Set(res.map((r) => r.idImovel))];
      const propMap: Record<number, Imovel> = {};
      await Promise.all(
        ids.map((id) =>
          imoveisService.getById(id).then((p) => { propMap[id] = p; }).catch(() => {}),
        ),
      );
      setProperties(propMap);
    } finally {
      setLoading(false);
    }
  }, [user, statusFilter, search, periodoDe, periodoAte]);

  useEffect(() => { fetch(); }, [fetch]);

  const handleCancel = async (r: Reserva) => {
    if (!confirm("Cancelar esta reserva?")) return;
    setCancelling(r.idReserva);
    try {
      await reservaService.update(r.idReserva, { status: "CANCELADA" });
      setReservations((prev) =>
        prev.map((res) => res.idReserva === r.idReserva ? { ...res, status: "CANCELADA" } : res),
      );
      if (selected?.idReserva === r.idReserva) setSelected({ ...r, status: "CANCELADA" });
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
            Minhas Reservas
          </h1>
          <p style={{ fontSize: 13, color: "var(--ink-3)", margin: "0 0 20px" }}>
            {reservations.length} reserva{reservations.length !== 1 ? "s" : ""} no total
          </p>

          <div style={{ display: "flex", gap: 10, marginBottom: 16, flexWrap: "wrap" }}>
            <div style={{ position: "relative", flex: 1, minWidth: 200 }}>
              <Search size={14} style={{ position: "absolute", left: 12, top: "50%", transform: "translateY(-50%)", color: "var(--ink-4)", pointerEvents: "none" }} />
              <input
                className="field-input"
                style={{ paddingLeft: 34 }}
                placeholder="Buscar por data, pagamento..."
                value={searchInput}
                onChange={(e) => setSearchInput(e.target.value)}
              />
            </div>
            <input className="field-input" type="date" value={periodoDe} onChange={(e) => setPeriodoDe(e.target.value)} title="De" style={{ width: 148 }} />
            <input className="field-input" type="date" value={periodoAte} onChange={(e) => setPeriodoAte(e.target.value)} title="Até" style={{ width: 148 }} />
            {(["ALL", "CONFIRMADA", "PENDENTE", "CANCELADA"] as StatusFilter[]).map((s) => (
              <button
                key={s}
                onClick={() => setStatusFilter(s)}
                style={{
                  padding: "8px 14px",
                  borderRadius: "var(--radius-sm)",
                  border: `1.5px solid ${statusFilter === s ? "var(--accent)" : "var(--border)"}`,
                  background: statusFilter === s ? "var(--accent-tint)" : "var(--surface)",
                  color: statusFilter === s ? "var(--accent)" : "var(--ink-3)",
                  fontSize: 12,
                  fontWeight: 600,
                  transition: "all 120ms ease",
                }}
              >
                {s === "ALL" ? "Todas" : s === "CONFIRMADA" ? "Confirmadas" : s === "PENDENTE" ? "Pendentes" : "Canceladas"}
              </button>
            ))}
          </div>
        </div>

        <div style={{ flex: 1, overflowY: "auto", padding: "0 28px 28px" }}>
          {loading ? (
            <div style={{ display: "flex", flexDirection: "column", gap: 10, paddingTop: 12 }}>
              {[1, 2, 3].map((i) => (
                <div key={i} style={{ height: 100, borderRadius: "var(--radius-lg)", background: "var(--canvas)" }} />
              ))}
            </div>
          ) : reservations.length === 0 ? (
            <div style={{ paddingTop: 48, textAlign: "center" }}>
              <CalendarDays size={40} style={{ color: "var(--ink-5)", margin: "0 auto 12px" }} />
              <p style={{ fontSize: 14, color: "var(--ink-3)", margin: "0 0 16px" }}>
                Você ainda não tem reservas.
              </p>
              <button onClick={() => navigate("/explore")} className="btn btn-primary btn-sm">
                Explorar imóveis
              </button>
            </div>
          ) : (
            <div style={{ display: "flex", flexDirection: "column", gap: 10, paddingTop: 12 }}>
              {reservations.map((r) => {
                const prop = properties[r.idImovel];
                const { label, cls } = statusInfo(r.status);
                const isActive = selected?.idReserva === r.idReserva;
                return (
                  <div
                    key={r.idReserva}
                    className="card"
                    onClick={() => setSelected(isActive ? null : r)}
                    style={{
                      padding: "16px 18px",
                      display: "flex",
                      gap: 14,
                      cursor: "pointer",
                      border: isActive ? "1.5px solid var(--accent)" : "1px solid var(--border)",
                      transition: "all 140ms ease",
                    }}
                  >
                    {prop?.fotos?.[0] ? (
                      <img
                        src={prop.fotos[0]}
                        alt={prop.titulo}
                        style={{ width: 72, height: 72, borderRadius: "var(--radius-sm)", objectFit: "cover", flexShrink: 0 }}
                      />
                    ) : (
                      <div style={{ width: 72, height: 72, borderRadius: "var(--radius-sm)", background: "var(--canvas)", display: "flex", alignItems: "center", justifyContent: "center", flexShrink: 0 }}>
                        <MapPin size={24} style={{ color: "var(--ink-5)" }} />
                      </div>
                    )}
                    <div style={{ flex: 1, minWidth: 0 }}>
                      <div style={{ fontSize: 14, fontWeight: 700, color: "var(--ink)", marginBottom: 3, overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap" }}>
                        {prop?.titulo ?? `Imóvel #${r.idImovel}`}
                      </div>
                      <div style={{ fontSize: 12, color: "var(--ink-3)", marginBottom: 6, display: "flex", alignItems: "center", gap: 4 }}>
                        <MapPin size={11} /> {prop?.cidade ?? "—"}
                      </div>
                      <div style={{ fontSize: 12, color: "var(--ink-2)" }}>
                        <CalendarDays size={11} style={{ display: "inline", marginRight: 4, verticalAlign: "middle" }} />
                        {r.dataInicio} → {r.dataFim}
                      </div>
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
        <ReservationDetail
          reserva={selected}
          property={properties[selected.idImovel]}
          onClose={() => setSelected(null)}
          onCancel={() => handleCancel(selected)}
          cancelling={cancelling === selected.idReserva}
          onViewProperty={() => { openDetail(selected.idImovel); setSelected(null); }}
        />
      )}
    </div>
  );
}

function ReservationDetail({
  reserva: r,
  property: p,
  onClose,
  onCancel,
  cancelling,
  onViewProperty,
}: {
  reserva: Reserva;
  property?: Imovel;
  onClose: () => void;
  onCancel: () => void;
  cancelling: boolean;
  onViewProperty: () => void;
}) {
  const { label, cls } = statusInfo(r.status);
  const nights = Math.max(
    0,
    Math.round((new Date(r.dataFim).getTime() - new Date(r.dataInicio).getTime()) / 86400000),
  );

  return (
    <div
      className="anim-slide-right"
      style={{
        width: 340,
        minWidth: 340,
        height: "100vh",
        overflowY: "auto",
        borderLeft: "1px solid var(--border)",
        background: "var(--surface)",
        display: "flex",
        flexDirection: "column",
      }}
    >
      <div style={{ padding: "20px 20px 0", display: "flex", alignItems: "center", justifyContent: "space-between", flexShrink: 0 }}>
        <h3 style={{ fontSize: 15, fontWeight: 700, color: "var(--ink)", margin: 0 }}>
          {reservaCode(r.idReserva)}
        </h3>
        <button
          onClick={onClose}
          style={{ background: "none", border: "none", color: "var(--ink-3)", display: "flex", padding: 4 }}
        >
          <X size={18} />
        </button>
      </div>

      <div style={{ padding: "16px 20px", flex: 1 }}>
        {p && (
          <div
            className="card"
            style={{ marginBottom: 16, overflow: "hidden", cursor: "pointer" }}
            onClick={onViewProperty}
          >
            {p.fotos?.[0] && (
              <img src={p.fotos[0]} alt={p.titulo} style={{ width: "100%", height: 120, objectFit: "cover" }} />
            )}
            <div style={{ padding: "12px 14px" }}>
              <div style={{ fontSize: 13, fontWeight: 700, color: "var(--ink)" }}>{p.titulo}</div>
              <div style={{ fontSize: 12, color: "var(--ink-3)" }}>{p.cidade}</div>
              <div style={{ fontSize: 11, color: "var(--accent)", fontWeight: 600, marginTop: 4 }}>
                Ver imóvel →
              </div>
            </div>
          </div>
        )}

        <div className="card" style={{ padding: "14px 16px", marginBottom: 12 }}>
          <Row label="Status" value={<span className={`badge ${cls}`}>{label}</span>} />
          <Row label="Check-in" value={r.dataInicio} />
          <Row label="Check-out" value={r.dataFim} />
          <Row label="Noites" value={String(nights)} />
          <Row label="Pagamento" value={r.formaPagamento || "—"} />
          <Row
            label="Total"
            value={
              <span style={{ fontWeight: 700, color: "var(--ink)", fontSize: 14 }}>
                {r.valorTotal.toLocaleString("pt-BR", { style: "currency", currency: "BRL" })}
              </span>
            }
            last
          />
        </div>

        {r.status === "PENDENTE" && (
          <button
            onClick={onCancel}
            disabled={cancelling}
            style={{
              width: "100%",
              padding: "10px",
              borderRadius: "var(--radius-md)",
              border: "1.5px solid var(--red)",
              background: "var(--red-tint)",
              color: "var(--red)",
              fontWeight: 600,
              fontSize: 13,
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              gap: 6,
            }}
          >
            <AlertCircle size={14} />
            {cancelling ? "Cancelando..." : "Cancelar reserva"}
          </button>
        )}
      </div>
    </div>
  );
}

function Row({ label, value, last }: { label: string; value: React.ReactNode; last?: boolean }) {
  return (
    <div
      style={{
        display: "flex",
        alignItems: "center",
        justifyContent: "space-between",
        paddingBottom: last ? 0 : 10,
        marginBottom: last ? 0 : 10,
        borderBottom: last ? "none" : "1px solid var(--border)",
      }}
    >
      <span style={{ fontSize: 12, color: "var(--ink-3)" }}>{label}</span>
      <span style={{ fontSize: 12, color: "var(--ink-2)", fontWeight: 600 }}>{value}</span>
    </div>
  );
}
