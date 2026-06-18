import { useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import { Building2, CalendarDays, TrendingUp, ArrowRight, Plus, MapPin, Users } from "lucide-react";
import {
  imoveisService,
  reservaService,
  type Imovel,
  type Reserva,
} from "../services/api";
import { useStore } from "../app/store";

function fmt(v: number) {
  return v.toLocaleString("pt-BR", { style: "currency", currency: "BRL", maximumFractionDigits: 0 });
}

function statusLabel(s: Reserva["status"]) {
  if (s === "CONFIRMADA") return { label: "Confirmada", cls: "badge-green" };
  if (s === "CANCELADA") return { label: "Cancelada", cls: "badge-red" };
  return { label: "Pendente", cls: "badge-amber" };
}

export default function HostDashboard() {
  const { user } = useStore();
  const navigate = useNavigate();
  const [listings, setListings] = useState<Imovel[]>([]);
  const [reservations, setReservations] = useState<Reserva[]>([]);
  const [loadingListings, setLoadingListings] = useState(true);
  const [loadingRes, setLoadingRes] = useState(true);

  useEffect(() => {
    if (!user) return;
    imoveisService
      .getByOwner(user.idUsuario)
      .then((d) => setListings(d))
      .finally(() => setLoadingListings(false));
    reservaService
      .getByAnfitriao(user.idUsuario)
      .then((r) => setReservations(r))
      .finally(() => setLoadingRes(false));
  }, [user]);

  const listingMap = Object.fromEntries(listings.map((l) => [l.idImovel, l.titulo]));

  const revenue = reservations
    .filter((r) => r.status === "CONFIRMADA")
    .reduce((acc, r) => acc + r.valorTotal, 0);
  const activeListings = listings.filter((l) => l.ativo);
  const pendingRes = reservations.filter((r) => r.status === "PENDENTE");
  const confirmedRes = reservations.filter((r) => r.status === "CONFIRMADA");

  return (
    <div style={{ padding: "32px 36px", maxWidth: 1000, margin: "0 auto" }}>
      <div style={{ display: "flex", alignItems: "center", justifyContent: "space-between", marginBottom: 28 }}>
        <div>
          <h1 style={{ fontSize: 26, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.04em", margin: "0 0 4px" }}>
            Dashboard do Anfitrião
          </h1>
          <p style={{ fontSize: 14, color: "var(--ink-3)", margin: 0 }}>
            Olá, {user?.nome.split(" ")[0]}. Veja o desempenho dos seus imóveis.
          </p>
        </div>
        <button
          onClick={() => navigate("/host/listings")}
          className="btn btn-primary"
        >
          <Plus size={15} /> Novo imóvel
        </button>
      </div>

      <div style={{ display: "grid", gridTemplateColumns: "repeat(4, 1fr)", gap: 12, marginBottom: 28 }}>
        <KpiCard
          icon={<Building2 size={20} />}
          label="Imóveis ativos"
          value={activeListings.length}
          color="var(--accent)"
          loading={loadingListings}
        />
        <KpiCard
          icon={<CalendarDays size={20} />}
          label="Reservas pendentes"
          value={pendingRes.length}
          color="var(--amber)"
          loading={loadingRes}
        />
        <KpiCard
          icon={<Users size={20} />}
          label="Reservas confirmadas"
          value={confirmedRes.length}
          color="var(--green)"
          loading={loadingRes}
        />
        <KpiCard
          icon={<TrendingUp size={20} />}
          label="Receita total"
          value={fmt(revenue)}
          color="var(--blue)"
          loading={loadingRes}
          isText
        />
      </div>

      <div style={{ display: "grid", gridTemplateColumns: "1.4fr 1fr", gap: 20 }}>
        <div>
          <SectionHeader
            title="Meus imóveis"
            action="Gerenciar"
            onAction={() => navigate("/host/listings")}
          />
          {loadingListings ? (
            <Skeleton rows={3} />
          ) : listings.length === 0 ? (
            <EmptyState
              message="Nenhum imóvel cadastrado ainda."
              cta="Cadastrar primeiro imóvel"
              onCta={() => navigate("/host/listings")}
            />
          ) : (
            <div style={{ display: "flex", flexDirection: "column", gap: 10 }}>
              {listings.slice(0, 4).map((p) => {
                const propRes = reservations.filter((r) => r.idImovel === p.idImovel);
                const propRevenue = propRes
                  .filter((r) => r.status === "CONFIRMADA")
                  .reduce((acc, r) => acc + r.valorTotal, 0);
                return (
                  <div
                    key={p.idImovel}
                    className="card"
                    style={{ padding: "14px 16px", display: "flex", gap: 12 }}
                  >
                    {p.fotos?.[0] ? (
                      <img
                        src={p.fotos[0]}
                        alt={p.titulo}
                        style={{
                          width: 56,
                          height: 56,
                          borderRadius: "var(--radius-sm)",
                          objectFit: "cover",
                          flexShrink: 0,
                        }}
                      />
                    ) : (
                      <div
                        style={{
                          width: 56,
                          height: 56,
                          borderRadius: "var(--radius-sm)",
                          background: "var(--canvas)",
                          display: "flex",
                          alignItems: "center",
                          justifyContent: "center",
                          flexShrink: 0,
                        }}
                      >
                        <Building2 size={20} style={{ color: "var(--ink-5)" }} />
                      </div>
                    )}
                    <div style={{ flex: 1, minWidth: 0 }}>
                      <div style={{ fontSize: 13, fontWeight: 700, color: "var(--ink)", marginBottom: 2, overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap" }}>
                        {p.titulo}
                      </div>
                      <div style={{ fontSize: 11, color: "var(--ink-3)", marginBottom: 6, display: "flex", alignItems: "center", gap: 4 }}>
                        <MapPin size={10} />
                        {p.cidade}
                      </div>
                      <div style={{ display: "flex", gap: 12 }}>
                        <span style={{ fontSize: 11, color: "var(--ink-3)" }}>
                          {propRes.length} reserva{propRes.length !== 1 ? "s" : ""}
                        </span>
                        <span style={{ fontSize: 11, fontWeight: 600, color: "var(--green)" }}>
                          {fmt(propRevenue)}
                        </span>
                      </div>
                    </div>
                    <span className={`badge ${p.ativo ? "badge-green" : "badge-ink"}`} style={{ alignSelf: "flex-start" }}>
                      {p.ativo ? "Ativo" : "Inativo"}
                    </span>
                  </div>
                );
              })}
            </div>
          )}
        </div>

        <div>
          <SectionHeader
            title="Reservas recentes"
            action="Ver todas"
            onAction={() => navigate("/host/reservations")}
          />
          {loadingRes ? (
            <Skeleton rows={4} />
          ) : reservations.length === 0 ? (
            <EmptyState message="Nenhuma reserva recebida." />
          ) : (
            <div style={{ display: "flex", flexDirection: "column", gap: 8 }}>
              {reservations.slice(0, 5).map((r) => {
                const { label, cls } = statusLabel(r.status);
                return (
                  <div
                    key={r.idReserva}
                    className="card"
                    style={{ padding: "12px 14px", display: "flex", alignItems: "center", gap: 10 }}
                  >
                    <div style={{ flex: 1, minWidth: 0 }}>
                      <div style={{ fontSize: 12, fontWeight: 600, color: "var(--ink)", overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap" }}>
                        {listingMap[r.idImovel] ?? "Imóvel #" + r.idImovel}
                      </div>
                      <div style={{ fontSize: 11, color: "var(--ink-3)" }}>
                        {r.dataInicio} → {r.dataFim}
                      </div>
                    </div>
                    <div style={{ textAlign: "right", flexShrink: 0 }}>
                      <div style={{ fontSize: 12, fontWeight: 700, color: "var(--ink)" }}>
                        {fmt(r.valorTotal)}
                      </div>
                      <span className={`badge ${cls}`} style={{ marginTop: 4, display: "inline-flex" }}>
                        {label}
                      </span>
                    </div>
                  </div>
                );
              })}
            </div>
          )}
        </div>
      </div>

      <div
        style={{
          marginTop: 24,
          padding: "20px 24px",
          borderRadius: "var(--radius-xl)",
          background: "linear-gradient(135deg, #0C0C11 0%, #1E1E2C 100%)",
          display: "flex",
          alignItems: "center",
          gap: 20,
          color: "#fff",
        }}
      >
        <TrendingUp size={28} style={{ color: "var(--accent-mid)", flexShrink: 0 }} />
        <div style={{ flex: 1 }}>
          <div style={{ fontSize: 15, fontWeight: 700, marginBottom: 3 }}>Relatório de receita</div>
          <div style={{ fontSize: 13, color: "rgba(255,255,255,0.6)" }}>
            Veja seu faturamento mensal, ocupação e projeções.
          </div>
        </div>
        <button
          onClick={() => navigate("/host/revenue")}
          style={{
            padding: "10px 20px",
            borderRadius: "var(--radius-md)",
            background: "var(--accent)",
            color: "#fff",
            border: "none",
            fontWeight: 600,
            fontSize: 13,
            display: "flex",
            alignItems: "center",
            gap: 6,
            flexShrink: 0,
          }}
        >
          Ver receita <ArrowRight size={14} />
        </button>
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
  isText,
}: {
  icon: React.ReactNode;
  label: string;
  value: string | number;
  color: string;
  loading?: boolean;
  isText?: boolean;
}) {
  return (
    <div className="stat-card">
      <div
        style={{
          width: 36,
          height: 36,
          borderRadius: "var(--radius-sm)",
          background: `${color}18`,
          color,
          display: "flex",
          alignItems: "center",
          justifyContent: "center",
          marginBottom: 14,
        }}
      >
        {icon}
      </div>
      <div
        style={{
          fontSize: isText ? 18 : 26,
          fontWeight: 800,
          color: "var(--ink)",
          letterSpacing: "-0.04em",
          marginBottom: 4,
        }}
      >
        {loading ? "—" : value}
      </div>
      <div style={{ fontSize: 12, color: "var(--ink-3)", fontWeight: 500 }}>{label}</div>
    </div>
  );
}

function SectionHeader({ title, action, onAction }: { title: string; action?: string; onAction?: () => void }) {
  return (
    <div style={{ display: "flex", alignItems: "center", justifyContent: "space-between", marginBottom: 12 }}>
      <h2 style={{ fontSize: 15, fontWeight: 700, color: "var(--ink)", margin: 0 }}>{title}</h2>
      {action && (
        <button
          onClick={onAction}
          style={{ fontSize: 12, color: "var(--accent)", background: "none", border: "none", fontWeight: 600, display: "flex", alignItems: "center", gap: 4 }}
        >
          {action} <ArrowRight size={12} />
        </button>
      )}
    </div>
  );
}

function EmptyState({ message, cta, onCta }: { message: string; cta?: string; onCta?: () => void }) {
  return (
    <div className="card" style={{ padding: 24, textAlign: "center" }}>
      <p style={{ fontSize: 13, color: "var(--ink-3)", margin: "0 0 10px" }}>{message}</p>
      {cta && (
        <button onClick={onCta} className="btn btn-primary btn-sm">
          {cta}
        </button>
      )}
    </div>
  );
}

function Skeleton({ rows = 3 }: { rows?: number }) {
  return (
    <div style={{ display: "flex", flexDirection: "column", gap: 8 }}>
      {Array.from({ length: rows }).map((_, i) => (
        <div key={i} className="card" style={{ height: 70, background: "var(--canvas)" }} />
      ))}
    </div>
  );
}
