import { Outlet, useNavigate, useLocation } from "react-router-dom";
import {
  Map,
  LayoutDashboard,
  Building2,
  CalendarDays,
  TrendingUp,
  Users,
  Sparkles,
  LogOut,
  ChevronLeft,
  ChevronRight,
  Home,
  Star,
} from "lucide-react";
import { useStore } from "../app/store";
import logoImg from "../assets/logo.png";

type NavItem = {
  to: string;
  label: string;
  icon: React.ReactNode;
};

const TIPO_LABEL: Record<string, string> = {
  HOSPEDE: "Hóspede",
  ANFITRIAO: "Anfitrião",
  ADMIN: "Admin",
};

function getNav(tipo: string): NavItem[] {
  if (tipo === "ADMIN") {
    return [
      { to: "/admin", label: "Dashboard", icon: <LayoutDashboard size={18} /> },
      { to: "/explore", label: "Explorar", icon: <Map size={18} /> },
      { to: "/admin/properties", label: "Imóveis", icon: <Building2 size={18} /> },
      { to: "/admin/reservations", label: "Reservas", icon: <CalendarDays size={18} /> },
      { to: "/admin/users", label: "Usuários", icon: <Users size={18} /> },
      { to: "/admin/amenities", label: "Comodidades", icon: <Sparkles size={18} /> },
    ];
  }
  if (tipo === "ANFITRIAO") {
    return [
      { to: "/host", label: "Dashboard", icon: <LayoutDashboard size={18} /> },
      { to: "/explore", label: "Explorar", icon: <Map size={18} /> },
      { to: "/host/listings", label: "Meus Imóveis", icon: <Building2 size={18} /> },
      { to: "/reservations", label: "Minhas Reservas", icon: <CalendarDays size={18} /> },
      { to: "/host/reservations", label: "Reservas Recebidas", icon: <Star size={18} /> },
      { to: "/host/revenue", label: "Receita", icon: <TrendingUp size={18} /> },
    ];
  }
  return [
    { to: "/dashboard", label: "Início", icon: <Home size={18} /> },
    { to: "/explore", label: "Explorar", icon: <Map size={18} /> },
    { to: "/reservations", label: "Minhas Reservas", icon: <CalendarDays size={18} /> },
  ];
}

export default function AppLayout() {
  const { user, logout, sidebarCollapsed, setSidebarCollapsed } = useStore();
  const navigate = useNavigate();
  const location = useLocation();

  if (!user) return null;

  const nav = getNav(user.tipo);
  const w = sidebarCollapsed ? "var(--sidebar-w-mini)" : "var(--sidebar-w)";

  const initials = user.nome
    .split(" ")
    .map((n) => n[0])
    .slice(0, 2)
    .join("")
    .toUpperCase();

  const handleLogout = () => {
    logout();
    navigate("/", { replace: true });
  };

  return (
    <div style={{ display: "flex", minHeight: "100vh", background: "var(--canvas)" }}>
      <aside
        className="hostly-sidebar"
        style={{
          width: w,
          minWidth: w,
          height: "100vh",
          position: "sticky",
          top: 0,
          display: "flex",
          flexDirection: "column",
          transition: "width 250ms ease",
          overflow: "hidden",
          flexShrink: 0,
          zIndex: 50,
        }}
      >
        <div
          style={{
            display: "flex",
            alignItems: "center",
            gap: 10,
            padding: sidebarCollapsed ? "20px 0" : "20px 16px",
            justifyContent: sidebarCollapsed ? "center" : "flex-start",
            borderBottom: "1px solid var(--border)",
            flexShrink: 0,
          }}
        >
          <img
            src={logoImg}
            alt="Hostly"
            style={{
              width: 32,
              height: 32,
              borderRadius: 8,
              objectFit: "cover",
              flexShrink: 0,
            }}
          />
          {!sidebarCollapsed && (
            <span
              style={{
                fontWeight: 800,
                fontSize: 17,
                color: "var(--ink)",
                letterSpacing: "-0.03em",
                whiteSpace: "nowrap",
              }}
            >
              Hostly
            </span>
          )}
        </div>

        <nav
          className="sidebar-scroll"
          style={{ flex: 1, padding: "12px 8px", display: "flex", flexDirection: "column", gap: 2 }}
        >
          {nav.map((item) => {
            const active = location.pathname === item.to;
            return (
              <button
                key={item.to}
                onClick={() => navigate(item.to)}
                title={sidebarCollapsed ? item.label : undefined}
                style={{
                  display: "flex",
                  alignItems: "center",
                  gap: 10,
                  padding: sidebarCollapsed ? "10px 0" : "10px 12px",
                  justifyContent: sidebarCollapsed ? "center" : "flex-start",
                  borderRadius: "var(--radius-md)",
                  border: "none",
                  background: active ? "var(--accent-tint)" : "transparent",
                  color: active ? "var(--accent)" : "var(--ink-3)",
                  fontWeight: active ? 600 : 500,
                  fontSize: 13,
                  transition: "all 130ms ease",
                  whiteSpace: "nowrap",
                  overflow: "hidden",
                }}
                onMouseEnter={(e) => {
                  if (!active) {
                    (e.currentTarget as HTMLElement).style.background = "var(--canvas)";
                    (e.currentTarget as HTMLElement).style.color = "var(--ink)";
                  }
                }}
                onMouseLeave={(e) => {
                  if (!active) {
                    (e.currentTarget as HTMLElement).style.background = "transparent";
                    (e.currentTarget as HTMLElement).style.color = "var(--ink-3)";
                  }
                }}
              >
                <span style={{ flexShrink: 0 }}>{item.icon}</span>
                {!sidebarCollapsed && <span>{item.label}</span>}
              </button>
            );
          })}

          {user.tipo === "HOSPEDE" && !sidebarCollapsed && (
            <div style={{ marginTop: "auto", paddingTop: 16 }}>
              <button
                onClick={() => navigate("/host/listings")}
                style={{
                  width: "100%",
                  padding: "10px 12px",
                  borderRadius: "var(--radius-md)",
                  background: "var(--accent)",
                  color: "#fff",
                  fontWeight: 600,
                  fontSize: 12,
                  border: "none",
                  transition: "background 130ms ease",
                }}
                onMouseEnter={(e) =>
                  ((e.currentTarget as HTMLElement).style.background = "var(--accent-hover)")
                }
                onMouseLeave={(e) =>
                  ((e.currentTarget as HTMLElement).style.background = "var(--accent)")
                }
              >
                Anunciar meu imóvel
              </button>
            </div>
          )}
        </nav>

        <div
          style={{
            borderTop: "1px solid var(--border)",
            padding: "12px 8px",
            display: "flex",
            flexDirection: "column",
            gap: 4,
            flexShrink: 0,
          }}
        >
          <button
            onClick={() => setSidebarCollapsed(!sidebarCollapsed)}
            style={{
              display: "flex",
              alignItems: "center",
              gap: 8,
              padding: sidebarCollapsed ? "8px 0" : "8px 12px",
              justifyContent: sidebarCollapsed ? "center" : "flex-start",
              borderRadius: "var(--radius-md)",
              border: "none",
              background: "transparent",
              color: "var(--ink-4)",
              fontSize: 12,
              transition: "all 130ms ease",
            }}
            onMouseEnter={(e) => {
              (e.currentTarget as HTMLElement).style.background = "var(--canvas)";
              (e.currentTarget as HTMLElement).style.color = "var(--ink-3)";
            }}
            onMouseLeave={(e) => {
              (e.currentTarget as HTMLElement).style.background = "transparent";
              (e.currentTarget as HTMLElement).style.color = "var(--ink-4)";
            }}
          >
            {sidebarCollapsed ? <ChevronRight size={16} /> : <ChevronLeft size={16} />}
            {!sidebarCollapsed && <span>Recolher</span>}
          </button>

          <button
            onClick={handleLogout}
            title={sidebarCollapsed ? "Sair" : undefined}
            style={{
              display: "flex",
              alignItems: "center",
              gap: 10,
              padding: sidebarCollapsed ? "10px 0" : "10px 12px",
              justifyContent: sidebarCollapsed ? "center" : "flex-start",
              borderRadius: "var(--radius-md)",
              border: "none",
              background: "transparent",
              color: "var(--ink-3)",
              fontSize: 13,
              fontWeight: 500,
              transition: "all 130ms ease",
              overflow: "hidden",
              whiteSpace: "nowrap",
            }}
            onMouseEnter={(e) => {
              (e.currentTarget as HTMLElement).style.background = "var(--red-tint)";
              (e.currentTarget as HTMLElement).style.color = "var(--red)";
            }}
            onMouseLeave={(e) => {
              (e.currentTarget as HTMLElement).style.background = "transparent";
              (e.currentTarget as HTMLElement).style.color = "var(--ink-3)";
            }}
          >
            {sidebarCollapsed ? (
              <LogOut size={18} />
            ) : (
              <>
                <div
                  style={{
                    width: 28,
                    height: 28,
                    borderRadius: "50%",
                    background: "var(--accent-tint)",
                    color: "var(--accent)",
                    display: "flex",
                    alignItems: "center",
                    justifyContent: "center",
                    fontWeight: 700,
                    fontSize: 11,
                    flexShrink: 0,
                  }}
                >
                  {initials}
                </div>
                <div style={{ flex: 1, minWidth: 0, textAlign: "left" }}>
                  <div
                    style={{
                      fontSize: 12,
                      fontWeight: 600,
                      color: "var(--ink)",
                      overflow: "hidden",
                      textOverflow: "ellipsis",
                      whiteSpace: "nowrap",
                    }}
                  >
                    {user.nome}
                  </div>
                  <div style={{ fontSize: 10, color: "var(--ink-3)" }}>
                    {TIPO_LABEL[user.tipo] ?? user.tipo}
                  </div>
                </div>
                <LogOut size={14} style={{ flexShrink: 0 }} />
              </>
            )}
          </button>
        </div>
      </aside>

      <main style={{ flex: 1, minWidth: 0, display: "flex", flexDirection: "column" }}>
        <Outlet />
      </main>
    </div>
  );
}
