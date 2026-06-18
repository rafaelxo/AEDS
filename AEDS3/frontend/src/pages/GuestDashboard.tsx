import { useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import { Map, CalendarDays, ArrowRight } from "lucide-react";
import { reservaService, imoveisService, type Reserva, type Imovel } from "../services/api";
import { useStore } from "../app/store";

function fmt(v: number) {
  return v.toLocaleString("pt-BR", { style: "currency", currency: "BRL", maximumFractionDigits: 0 });
}

function statusLabel(s: Reserva["status"]) {
  if (s === "CONFIRMADA") return { label: "Confirmada", cls: "badge-green" };
  if (s === "CANCELADA") return { label: "Cancelada", cls: "badge-red" };
  return { label: "Pendente", cls: "badge-amber" };
}

export default function GuestDashboard() {
  const { user } = useStore();
  const navigate = useNavigate();
  const [reservations, setReservations] = useState<Reserva[]>([]);
  const [propMap, setPropMap] = useState<Record<number, Imovel>>({});
  const [loadingRes, setLoadingRes] = useState(true);

  useEffect(() => {
    if (!user) return;
    reservaService.getByHospede(user.idUsuario).then(async (res) => {
      const sliced = res.slice(0, 3);
      setReservations(sliced);
      const ids = [...new Set(sliced.map((r) => r.idImovel))];
      const map: Record<number, Imovel> = {};
      await Promise.all(ids.map((id) => imoveisService.getById(id).then((p) => { map[id] = p; }).catch(() => {})));
      setPropMap(map);
    }).finally(() => setLoadingRes(false));
  }, [user]);

  const active = reservations.filter((r) => r.status === "CONFIRMADA");
  const pending = reservations.filter((r) => r.status === "PENDENTE");

  return (
    <div style={{ padding: "32px 36px", maxWidth: 960, margin: "0 auto" }}>
      <div style={{ marginBottom: 32 }}>
        <h1 style={{ fontSize: 26, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.04em", margin: "0 0 6px" }}>
          Olá, {user?.nome.split(" ")[0]} 👋
        </h1>
        <p style={{ fontSize: 14, color: "var(--ink-3)", margin: 0 }}>
          Bem-vindo ao Hostly. O que você gostaria de fazer hoje?
        </p>
      </div>

      <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 12, marginBottom: 32 }}>
        <QuickAction
          icon={<Map size={20} />}
          title="Explorar imóveis"
          description="Navegue pelo mapa e encontre seu próximo destino"
          onClick={() => navigate("/explore")}
          accent
        />
        <QuickAction
          icon={<CalendarDays size={20} />}
          title="Minhas reservas"
          description="Gerencie suas reservas ativas e passadas"
          onClick={() => navigate("/reservations")}
        />
      </div>

      <div style={{ display: "grid", gridTemplateColumns: "repeat(3, 1fr)", gap: 12, marginBottom: 32 }}>
        <StatCard label="Reservas ativas" value={active.length} color="var(--green)" />
        <StatCard label="Pendentes" value={pending.length} color="var(--amber)" />
        <StatCard label="Total de viagens" value={reservations.length} color="var(--accent)" />
      </div>

      <div style={{ marginBottom: 32 }}>
        <SectionHeader title="Reservas recentes" action="Ver todas" onAction={() => navigate("/reservations")} />
        {loadingRes ? (
          <Skeleton />
        ) : reservations.length === 0 ? (
          <EmptyState
            message="Você ainda não tem reservas."
            cta="Explorar imóveis"
            onCta={() => navigate("/explore")}
          />
        ) : (
          <div style={{ display: "flex", flexDirection: "column", gap: 8 }}>
            {reservations.map((r) => {
              const { label, cls } = statusLabel(r.status);
              return (
                <div
                  key={r.idReserva}
                  className="card"
                  style={{ padding: "14px 18px", display: "flex", alignItems: "center", gap: 14 }}
                >
                  <div
                    style={{
                      width: 40,
                      height: 40,
                      borderRadius: "var(--radius-md)",
                      background: "var(--canvas)",
                      display: "flex",
                      alignItems: "center",
                      justifyContent: "center",
                      flexShrink: 0,
                    }}
                  >
                    <CalendarDays size={18} style={{ color: "var(--accent)" }} />
                  </div>
                  <div style={{ flex: 1 }}>
                    <div style={{ fontSize: 13, fontWeight: 600, color: "var(--ink)", marginBottom: 2, overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap" }}>
                      {propMap[r.idImovel]?.titulo ?? "Imóvel #" + r.idImovel}
                    </div>
                    <div style={{ fontSize: 12, color: "var(--ink-3)" }}>
                      {r.dataInicio} → {r.dataFim} · {fmt(r.valorTotal)}
                    </div>
                  </div>
                  <span className={`badge ${cls}`}>{label}</span>
                </div>
              );
            })}
          </div>
        )}
      </div>

      {user?.tipo === "HOSPEDE" && (
        <div
          style={{
            padding: "24px 28px",
            borderRadius: "var(--radius-xl)",
            background: "linear-gradient(135deg, var(--accent-tint) 0%, #FFF7F4 100%)",
            border: "1px solid var(--accent-mid)",
            display: "flex",
            alignItems: "center",
            gap: 20,
          }}
        >
          <div style={{ flex: 1 }}>
            <h3 style={{ fontSize: 16, fontWeight: 700, color: "var(--ink)", margin: "0 0 4px" }}>
              Torne-se um anfitrião
            </h3>
            <p style={{ fontSize: 13, color: "var(--ink-3)", margin: 0 }}>
              Anuncie seu imóvel e comece a receber hóspedes. É simples e gratuito.
            </p>
          </div>
          <button
            onClick={() => navigate("/host/listings")}
            className="btn btn-primary"
            style={{ flexShrink: 0 }}
          >
            Anunciar imóvel <ArrowRight size={14} />
          </button>
        </div>
      )}
    </div>
  );
}

function QuickAction({
  icon,
  title,
  description,
  onClick,
  accent,
}: {
  icon: React.ReactNode;
  title: string;
  description: string;
  onClick: () => void;
  accent?: boolean;
}) {
  return (
    <button
      onClick={onClick}
      className="card card-hover"
      style={{
        padding: "20px",
        display: "flex",
        flexDirection: "column",
        alignItems: "flex-start",
        gap: 10,
        border: "none",
        cursor: "pointer",
        textAlign: "left",
        background: accent ? "var(--accent)" : "var(--surface)",
      }}
    >
      <span style={{ color: accent ? "rgba(255,255,255,0.8)" : "var(--accent)" }}>{icon}</span>
      <div>
        <div style={{ fontSize: 14, fontWeight: 700, color: accent ? "#fff" : "var(--ink)", marginBottom: 4 }}>
          {title}
        </div>
        <div style={{ fontSize: 12, color: accent ? "rgba(255,255,255,0.72)" : "var(--ink-3)" }}>
          {description}
        </div>
      </div>
    </button>
  );
}

function StatCard({ label, value, color }: { label: string; value: number; color: string }) {
  return (
    <div className="card" style={{ padding: "18px 20px" }}>
      <div style={{ fontSize: 28, fontWeight: 800, color, letterSpacing: "-0.05em", marginBottom: 4 }}>
        {value}
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
    <div className="card" style={{ padding: 32, textAlign: "center" }}>
      <p style={{ fontSize: 13, color: "var(--ink-3)", margin: "0 0 12px" }}>{message}</p>
      {cta && (
        <button onClick={onCta} className="btn btn-secondary btn-sm">
          {cta}
        </button>
      )}
    </div>
  );
}

function Skeleton() {
  return (
    <div style={{ display: "flex", flexDirection: "column", gap: 8 }}>
      {[1, 2].map((i) => (
        <div key={i} className="card" style={{ padding: "14px 18px", height: 64, background: "var(--canvas)" }} />
      ))}
    </div>
  );
}
