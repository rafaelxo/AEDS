import { useEffect, useState, useCallback } from "react";
import { Search, CalendarDays, Trash2 } from "lucide-react";
import { reservaService, imoveisService, usuarioService, type Reserva } from "../services/api";

function reservaCode(id: number): string {
  return "RES-" + id.toString(36).toUpperCase().padStart(3, "0");
}
function abbrevName(name: string): string {
  const parts = name.trim().split(/\s+/);
  if (parts.length <= 1 || name.length <= 18) return name;
  return parts[0] + " " + parts.slice(1).map((p) => p[0] + ".").join(" ");
}
function abbrevTitle(title: string): string {
  return title.length > 26 ? title.slice(0, 26) + "…" : title;
}

function fmt(v: number) {
  return v.toLocaleString("pt-BR", { style: "currency", currency: "BRL", maximumFractionDigits: 0 });
}

function statusInfo(s: Reserva["status"]) {
  if (s === "CONFIRMADA") return { label: "Confirmada", cls: "badge-green" };
  if (s === "CANCELADA") return { label: "Cancelada", cls: "badge-red" };
  return { label: "Pendente", cls: "badge-amber" };
}

type StatusFilter = "ALL" | Reserva["status"];

export default function AdminReservations() {
  const [reservations, setReservations] = useState<Reserva[]>([]);
  const [loading, setLoading] = useState(true);
  const [searchInput, setSearchInput] = useState("");
  const [search, setSearch] = useState("");
  const [statusFilter, setStatusFilter] = useState<StatusFilter>("ALL");
  const [periodoDe, setPeriodoDe] = useState("");
  const [periodoAte, setPeriodoAte] = useState("");
  const [deleting, setDeleting] = useState<number | null>(null);
  const [hospedeMap, setHospedeMap] = useState<Record<number, string>>({});
  const [imovelMap, setImovelMap] = useState<Record<number, string>>({});

  useEffect(() => {
    const t = setTimeout(() => setSearch(searchInput), 400);
    return () => clearTimeout(t);
  }, [searchInput]);

  const fetch = useCallback(async () => {
    setLoading(true);
    try {
      const params: Parameters<typeof reservaService.getAll>[0] = {};
      if (statusFilter !== "ALL") params.status = statusFilter;
      if (search.trim()) params.busca = search.trim();
      if (periodoDe) params.periodoDe = periodoDe;
      if (periodoAte) params.periodoAte = periodoAte;
      const [data, users, imoveis] = await Promise.all([
        reservaService.getAll(params),
        usuarioService.getAll(),
        imoveisService.getAll(),
      ]);
      setReservations(data);
      setHospedeMap(Object.fromEntries(users.map((u) => [u.idUsuario, u.nome])));
      setImovelMap(Object.fromEntries(imoveis.map((p) => [p.idImovel, p.titulo])));
    } finally {
      setLoading(false);
    }
  }, [statusFilter, search, periodoDe, periodoAte]);

  useEffect(() => { fetch(); }, [fetch]);

  const handleDelete = async (r: Reserva) => {
    if (!confirm(`Excluir reserva #${r.idReserva}?`)) return;
    setDeleting(r.idReserva);
    try {
      await reservaService.delete(r.idReserva);
      setReservations((prev) => prev.filter((x) => x.idReserva !== r.idReserva));
    } catch (e) {
      alert(e instanceof Error ? e.message : "Erro ao excluir");
    } finally {
      setDeleting(null);
    }
  };

  return (
    <div style={{ padding: "28px 36px" }}>
      <div style={{ display: "flex", alignItems: "center", justifyContent: "space-between", marginBottom: 24, flexWrap: "wrap", gap: 12 }}>
        <div>
          <h1 style={{ fontSize: 22, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.04em", margin: "0 0 4px" }}>Reservas</h1>
          <p style={{ fontSize: 13, color: "var(--ink-3)", margin: 0 }}>{reservations.length} reserva(s)</p>
        </div>
        <div style={{ display: "flex", gap: 10, flexWrap: "wrap" }}>
          <div style={{ position: "relative" }}>
            <Search size={14} style={{ position: "absolute", left: 12, top: "50%", transform: "translateY(-50%)", color: "var(--ink-4)", pointerEvents: "none" }} />
            <input className="field-input" style={{ paddingLeft: 34 }} placeholder="Buscar reserva..." value={searchInput} onChange={(e) => setSearchInput(e.target.value)} />
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

      <div className="card" style={{ overflow: "hidden" }}>
        {loading ? (
          <div style={{ padding: 40, textAlign: "center" }}>
            <div className="anim-spin" style={{ width: 24, height: 24, border: "3px solid var(--border)", borderTopColor: "var(--accent)", borderRadius: "50%", margin: "0 auto" }} />
          </div>
        ) : reservations.length === 0 ? (
          <div style={{ padding: 48, textAlign: "center" }}>
            <CalendarDays size={36} style={{ color: "var(--ink-5)", margin: "0 auto 12px" }} />
            <p style={{ fontSize: 14, color: "var(--ink-3)", margin: 0 }}>Nenhuma reserva encontrada.</p>
          </div>
        ) : (
          <table className="data-table">
            <thead>
              <tr>
                <th>#</th>
                <th>Imóvel</th>
                <th>Hóspede</th>
                <th>Período</th>
                <th>Pagamento</th>
                <th>Total</th>
                <th>Status</th>
                <th style={{ textAlign: "right" }}>Ações</th>
              </tr>
            </thead>
            <tbody>
              {reservations.map((r) => {
                const { label, cls } = statusInfo(r.status);
                return (
                  <tr key={r.idReserva}>
                    <td style={{ fontSize: 11, color: "var(--ink-4)", fontFamily: "monospace", fontWeight: 600, letterSpacing: "0.04em" }}>{reservaCode(r.idReserva)}</td>
                    <td style={{ fontSize: 12, color: "var(--ink-2)" }}>{abbrevTitle(imovelMap[r.idImovel] ?? "Imóvel #" + r.idImovel)}</td>
                    <td style={{ fontSize: 12, color: "var(--ink-2)" }}>{abbrevName(hospedeMap[r.idHospede] ?? "Hóspede #" + r.idHospede)}</td>
                    <td style={{ fontSize: 12 }}>
                      <div style={{ color: "var(--ink-2)" }}>{r.dataInicio}</div>
                      <div style={{ color: "var(--ink-3)" }}>→ {r.dataFim}</div>
                    </td>
                    <td style={{ fontSize: 12, color: "var(--ink-2)" }}>{r.formaPagamento || "—"}</td>
                    <td style={{ fontSize: 13, fontWeight: 700 }}>{fmt(r.valorTotal)}</td>
                    <td><span className={`badge ${cls}`}>{label}</span></td>
                    <td style={{ textAlign: "right" }}>
                      <button onClick={() => handleDelete(r)} disabled={deleting === r.idReserva}
                        style={{ padding: "6px 10px", borderRadius: "var(--radius-sm)", border: "none", background: "var(--red-tint)", color: "var(--red)", display: "flex", alignItems: "center", marginLeft: "auto" }}>
                        {deleting === r.idReserva ? "..." : <Trash2 size={13} />}
                      </button>
                    </td>
                  </tr>
                );
              })}
            </tbody>
          </table>
        )}
      </div>
    </div>
  );
}
