import { useEffect, useState } from "react";
import { TrendingUp, Building2, CalendarDays, DollarSign, MapPin } from "lucide-react";
import { imoveisService, reservaService, type Imovel, type Reserva } from "../services/api";
import { useStore } from "../app/store";

function fmt(v: number) {
  return v.toLocaleString("pt-BR", { style: "currency", currency: "BRL", maximumFractionDigits: 0 });
}

interface PropRevenue {
  property: Imovel;
  reservations: Reserva[];
  revenue: number;
  confirmed: number;
}

export default function HostRevenue() {
  const { user } = useStore();
  const [propRevenues, setPropRevenues] = useState<PropRevenue[]>([]);
  const [allReservations, setAllReservations] = useState<Reserva[]>([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    if (!user) return;
    Promise.all([
      imoveisService.getByOwner(user.idUsuario),
      reservaService.getByAnfitriao(user.idUsuario),
    ])
      .then(([listings, reservas]) => {
        setAllReservations(reservas);
        const data: PropRevenue[] = listings.map((p) => {
          const pRes = reservas.filter((r) => r.idImovel === p.idImovel);
          const confirmed = pRes.filter((r) => r.status === "CONFIRMADA");
          return {
            property: p,
            reservations: pRes,
            revenue: confirmed.reduce((acc, r) => acc + r.valorTotal, 0),
            confirmed: confirmed.length,
          };
        });
        data.sort((a, b) => b.revenue - a.revenue);
        setPropRevenues(data);
      })
      .finally(() => setLoading(false));
  }, [user]);

  const totalRevenue = propRevenues.reduce((acc, p) => acc + p.revenue, 0);
  const totalConfirmed = allReservations.filter((r) => r.status === "CONFIRMADA").length;
  const totalPending = allReservations.filter((r) => r.status === "PENDENTE").length;
  const avgTicket = totalConfirmed > 0 ? totalRevenue / totalConfirmed : 0;
  const best = propRevenues[0];

  return (
    <div style={{ padding: "32px 36px", maxWidth: 900, margin: "0 auto" }}>
      <div style={{ marginBottom: 28 }}>
        <h1 style={{ fontSize: 22, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.04em", margin: "0 0 4px" }}>
          Receita
        </h1>
        <p style={{ fontSize: 13, color: "var(--ink-3)", margin: 0 }}>
          Resumo de ganhos dos seus imóveis
        </p>
      </div>

      <div style={{ display: "grid", gridTemplateColumns: "repeat(4, 1fr)", gap: 12, marginBottom: 28 }}>
        <KpiCard icon={<DollarSign size={20} />} label="Receita total" value={fmt(totalRevenue)} color="var(--green)" loading={loading} />
        <KpiCard icon={<CalendarDays size={20} />} label="Reservas confirmadas" value={totalConfirmed} color="var(--blue)" loading={loading} />
        <KpiCard icon={<TrendingUp size={20} />} label="Ticket médio" value={fmt(avgTicket)} color="var(--accent)" loading={loading} />
        <KpiCard icon={<Building2 size={20} />} label="Pendentes" value={totalPending} color="var(--amber)" loading={loading} />
      </div>

      {!loading && best && best.revenue > 0 && (
        <div
          style={{
            marginBottom: 24,
            padding: "20px 24px",
            borderRadius: "var(--radius-xl)",
            background: "linear-gradient(135deg, #0C0C11 0%, #1E1E2C 100%)",
            display: "flex",
            alignItems: "center",
            gap: 20,
            color: "#fff",
          }}
        >
          {best.property.fotos?.[0] && (
            <img
              src={best.property.fotos[0]}
              alt={best.property.titulo}
              style={{ width: 64, height: 64, borderRadius: "var(--radius-md)", objectFit: "cover", flexShrink: 0 }}
            />
          )}
          <div style={{ flex: 1 }}>
            <div style={{ fontSize: 10, fontWeight: 700, color: "rgba(255,255,255,0.5)", textTransform: "uppercase", letterSpacing: "0.08em", marginBottom: 4 }}>
              Melhor desempenho
            </div>
            <div style={{ fontSize: 16, fontWeight: 700, marginBottom: 2 }}>{best.property.titulo}</div>
            <div style={{ fontSize: 13, color: "rgba(255,255,255,0.6)", display: "flex", alignItems: "center", gap: 4 }}>
              <MapPin size={12} /> {best.property.cidade}
            </div>
          </div>
          <div style={{ textAlign: "right", flexShrink: 0 }}>
            <div style={{ fontSize: 24, fontWeight: 800, color: "var(--accent-mid)", letterSpacing: "-0.04em" }}>
              {fmt(best.revenue)}
            </div>
            <div style={{ fontSize: 12, color: "rgba(255,255,255,0.5)" }}>
              {best.confirmed} reserva{best.confirmed !== 1 ? "s" : ""}
            </div>
          </div>
        </div>
      )}

      <div className="card" style={{ overflow: "hidden" }}>
        <div style={{ padding: "16px 20px", borderBottom: "1px solid var(--border)" }}>
          <h2 style={{ fontSize: 14, fontWeight: 700, color: "var(--ink)", margin: 0 }}>
            Receita por imóvel
          </h2>
        </div>
        {loading ? (
          <div style={{ padding: 32, textAlign: "center" }}>
            <div className="anim-spin" style={{ width: 24, height: 24, border: "3px solid var(--border)", borderTopColor: "var(--accent)", borderRadius: "50%", margin: "0 auto" }} />
          </div>
        ) : propRevenues.length === 0 ? (
          <div style={{ padding: 40, textAlign: "center", color: "var(--ink-3)", fontSize: 13 }}>
            Nenhum dado de receita disponível.
          </div>
        ) : (
          <div>
            {propRevenues.map((item, i) => {
              const pct = totalRevenue > 0 ? (item.revenue / totalRevenue) * 100 : 0;
              return (
                <div
                  key={item.property.idImovel}
                  style={{
                    padding: "14px 20px",
                    borderBottom: i < propRevenues.length - 1 ? "1px solid var(--border)" : "none",
                    display: "flex",
                    alignItems: "center",
                    gap: 14,
                  }}
                >
                  <span style={{ fontSize: 11, fontWeight: 700, color: "var(--ink-4)", width: 20, textAlign: "center" }}>
                    #{i + 1}
                  </span>
                  {item.property.fotos?.[0] ? (
                    <img src={item.property.fotos[0]} alt="" style={{ width: 44, height: 44, borderRadius: "var(--radius-sm)", objectFit: "cover", flexShrink: 0 }} />
                  ) : (
                    <div style={{ width: 44, height: 44, borderRadius: "var(--radius-sm)", background: "var(--canvas)", display: "flex", alignItems: "center", justifyContent: "center", flexShrink: 0 }}>
                      <Building2 size={18} style={{ color: "var(--ink-5)" }} />
                    </div>
                  )}
                  <div style={{ flex: 1, minWidth: 0 }}>
                    <div style={{ fontSize: 13, fontWeight: 600, color: "var(--ink)", marginBottom: 2, overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap" }}>
                      {item.property.titulo}
                    </div>
                    <div style={{ fontSize: 11, color: "var(--ink-3)", marginBottom: 6 }}>
                      {item.confirmed} confirmada{item.confirmed !== 1 ? "s" : ""} · {item.reservations.length} total
                    </div>
                    <div style={{ display: "flex", alignItems: "center", justifyContent: "space-between", marginBottom: 4 }}>
                      <span style={{ fontSize: 10, fontWeight: 600, color: "var(--ink-4)", letterSpacing: "0.02em" }}>
                        Participação na receita total
                      </span>
                      <span style={{ fontSize: 10, fontWeight: 700, color: "var(--accent)" }}>
                        {pct.toFixed(0)}%
                      </span>
                    </div>
                    <div style={{ height: 4, borderRadius: 99, background: "var(--border)", overflow: "hidden" }}>
                      <div style={{ height: "100%", width: `${pct}%`, background: "var(--accent)", borderRadius: 99, transition: "width 600ms ease" }} />
                    </div>
                  </div>
                  <div style={{ textAlign: "right", flexShrink: 0 }}>
                    <div style={{ fontSize: 15, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.03em" }}>
                      {fmt(item.revenue)}
                    </div>
                    <div style={{ fontSize: 11, color: "var(--ink-4)" }}>
                      {item.confirmed} reserva{item.confirmed !== 1 ? "s" : ""} confirmada{item.confirmed !== 1 ? "s" : ""}
                    </div>
                  </div>
                </div>
              );
            })}
          </div>
        )}
      </div>
    </div>
  );
}

function KpiCard({
  icon,
  label,
  value,
  color,
  loading,
}: {
  icon: React.ReactNode;
  label: string;
  value: string | number;
  color: string;
  loading?: boolean;
}) {
  return (
    <div className="stat-card">
      <div style={{ width: 36, height: 36, borderRadius: "var(--radius-sm)", background: `${color}18`, color, display: "flex", alignItems: "center", justifyContent: "center", marginBottom: 14 }}>
        {icon}
      </div>
      <div style={{ fontSize: 20, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.04em", marginBottom: 4 }}>
        {loading ? "—" : value}
      </div>
      <div style={{ fontSize: 12, color: "var(--ink-3)", fontWeight: 500 }}>{label}</div>
    </div>
  );
}
