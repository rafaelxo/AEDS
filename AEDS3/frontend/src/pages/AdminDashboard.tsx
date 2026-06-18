import { useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import {
  Building2,
  Users,
  CalendarDays,
  TrendingUp,
  ArrowRight,
  Sparkles,
  Activity,
  FileArchive,
  CheckCircle2,
  Clock,
  Download,
  RotateCcw,
} from "lucide-react";
import {
  dashboardService,
  backupService,
  type DashboardStats,
  type BackupInfo,
  type AlgoritmoCompressao,
} from "../services/api";

function fmt(v: number) {
  return v.toLocaleString("pt-BR", { style: "currency", currency: "BRL", maximumFractionDigits: 0 });
}

function formatBytes(n: number): string {
  if (n < 1024) return `${n} B`;
  if (n < 1024 * 1024) return `${(n / 1024).toFixed(1)} KB`;
  return `${(n / (1024 * 1024)).toFixed(2)} MB`;
}

export default function AdminDashboard() {
  const navigate = useNavigate();
  const [stats, setStats] = useState<DashboardStats | null>(null);
  const [loading, setLoading] = useState(true);
  const [backups, setBackups] = useState<BackupInfo[]>([]);
  const [creatingBackup, setCreatingBackup] = useState<AlgoritmoCompressao | null>(null);
  const [restoringFile, setRestoringFile] = useState<string | null>(null);
  const [restoreSuccess, setRestoreSuccess] = useState<string | null>(null);

  const refreshBackups = () => {
    backupService.list().then((list) => {
      const sorted = [...list].sort((a, b) => b.arquivo.localeCompare(a.arquivo));
      setBackups(sorted);
    }).catch(() => { });
  };

  useEffect(() => {
    dashboardService.getStats().then(setStats).finally(() => setLoading(false));
    refreshBackups();
  }, []);

  const handleCreateBackup = async (algo: AlgoritmoCompressao) => {
    setCreatingBackup(algo);
    try {
      await backupService.create(algo);
      refreshBackups();
    } catch (e) {
      alert(e instanceof Error ? e.message : "Erro ao criar backup");
    } finally {
      setCreatingBackup(null);
    }
  };

  const handleRestore = async (arquivo: string) => {
    if (!confirm(`Restaurar "${arquivo}"?\n\nOs dados atuais serão substituídos pelos dados do backup.`)) return;
    setRestoringFile(arquivo);
    setRestoreSuccess(null);
    try {
      await backupService.restore(arquivo);
      setRestoreSuccess(arquivo);
      refreshBackups();
    } catch (e) {
      alert(e instanceof Error ? e.message : "Erro ao restaurar backup");
    } finally {
      setRestoringFile(null);
    }
  };

  const sections = [
    {
      label: "Imóveis",
      description: "Gerencie todos os imóveis da plataforma",
      icon: <Building2 size={22} />,
      color: "var(--accent)",
      to: "/admin/properties",
      value: stats?.totalImoveis,
    },
    {
      label: "Usuários",
      description: "Administre anfitriões e hóspedes",
      icon: <Users size={22} />,
      color: "var(--blue)",
      to: "/admin/users",
      value: stats?.totalAnfitrioes,
    },
    {
      label: "Reservas",
      description: "Monitore todas as reservas ativas",
      icon: <CalendarDays size={22} />,
      color: "var(--green)",
      to: "/admin/reservations",
      value: stats?.totalReservas,
    },
    {
      label: "Comodidades",
      description: "Gerencie o catálogo de comodidades",
      icon: <Sparkles size={22} />,
      color: "var(--amber)",
      to: "/admin/amenities",
      value: null,
    },
  ];

  return (
    <div style={{ padding: "32px 36px", maxWidth: 960, margin: "0 auto" }}>
      <div style={{ marginBottom: 32 }}>
        <div style={{ display: "flex", alignItems: "center", gap: 10, marginBottom: 8 }}>
          <Activity size={20} style={{ color: "var(--accent)" }} />
          <span style={{ fontSize: 11, fontWeight: 700, color: "var(--ink-3)", textTransform: "uppercase", letterSpacing: "0.08em" }}>
            Painel Administrativo
          </span>
        </div>
        <h1 style={{ fontSize: 28, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.04em", margin: 0 }}>
          Operações da Plataforma
        </h1>
      </div>

      <div style={{ display: "grid", gridTemplateColumns: "repeat(3, 1fr)", gap: 12, marginBottom: 32 }}>
        <BigKpi
          label="Imóveis ativos"
          value={loading ? "—" : String(stats?.totalImoveis ?? 0)}
          icon={<Building2 size={24} />}
          color="var(--accent)"
        />
        <BigKpi
          label="Reservas totais"
          value={loading ? "—" : String(stats?.totalReservas ?? 0)}
          icon={<CalendarDays size={24} />}
          color="var(--blue)"
        />
        <BigKpi
          label="Receita da plataforma"
          value={loading ? "—" : fmt(stats?.receitaTotal ?? 0)}
          icon={<TrendingUp size={24} />}
          color="var(--green)"
          isText
        />
      </div>

      <div>
        <h2 style={{ fontSize: 14, fontWeight: 700, color: "var(--ink-3)", textTransform: "uppercase", letterSpacing: "0.06em", margin: "0 0 14px" }}>
          Gerenciamento
        </h2>
        <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 12 }}>
          {sections.map((s) => (
            <button
              key={s.to}
              onClick={() => navigate(s.to)}
              className="card card-hover"
              style={{
                padding: "22px 24px",
                display: "flex",
                alignItems: "center",
                gap: 16,
                border: "none",
                cursor: "pointer",
                textAlign: "left",
              }}
            >
              <div
                style={{
                  width: 48,
                  height: 48,
                  borderRadius: "var(--radius-md)",
                  background: `${s.color}14`,
                  color: s.color,
                  display: "flex",
                  alignItems: "center",
                  justifyContent: "center",
                  flexShrink: 0,
                }}
              >
                {s.icon}
              </div>
              <div style={{ flex: 1 }}>
                <div style={{ display: "flex", alignItems: "center", gap: 8, marginBottom: 3 }}>
                  <span style={{ fontSize: 15, fontWeight: 700, color: "var(--ink)" }}>{s.label}</span>
                  {s.value != null && (
                    <span
                      style={{
                        padding: "2px 8px",
                        borderRadius: "99px",
                        background: `${s.color}14`,
                        color: s.color,
                        fontSize: 11,
                        fontWeight: 700,
                      }}
                    >
                      {loading ? "—" : s.value}
                    </span>
                  )}
                </div>
                <div style={{ fontSize: 12, color: "var(--ink-3)" }}>{s.description}</div>
              </div>
              <ArrowRight size={16} style={{ color: "var(--ink-4)", flexShrink: 0 }} />
            </button>
          ))}
        </div>
      </div>

      <div style={{ marginTop: 20 }}>
        <h2 style={{ fontSize: 14, fontWeight: 700, color: "var(--ink-3)", textTransform: "uppercase", letterSpacing: "0.06em", margin: "0 0 14px" }}>
          Integridade dos Dados
        </h2>

        <div
          className="card"
          style={{ padding: "16px 20px", display: "flex", alignItems: "center", gap: 14, marginBottom: 10 }}
        >
          <div
            style={{
              width: 38,
              height: 38,
              borderRadius: "var(--radius-md)",
              background: backups.length > 0 ? "var(--green-tint)" : "var(--canvas)",
              color: backups.length > 0 ? "var(--green)" : "var(--ink-4)",
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              flexShrink: 0,
            }}
          >
            {backups.length > 0 ? <CheckCircle2 size={18} /> : <FileArchive size={18} />}
          </div>
          <div style={{ flex: 1, minWidth: 0 }}>
            <div style={{ fontSize: 13, fontWeight: 700, color: "var(--ink)", marginBottom: 2 }}>
              {backups.length > 0 ? `${backups.length} backup(s) disponível(is)` : "Nenhum backup criado ainda"}
            </div>
            <div style={{ fontSize: 12, color: "var(--ink-3)" }}>
              Criado automaticamente a cada 5 escritas — Huffman e LZW alternados.
            </div>
          </div>
          <div style={{ display: "flex", gap: 6, flexShrink: 0 }}>
            {(["huffman", "lzw"] as AlgoritmoCompressao[]).map((algo) => (
              <button
                key={algo}
                onClick={() => handleCreateBackup(algo)}
                disabled={creatingBackup !== null || restoringFile !== null}
                className="btn btn-secondary btn-sm"
                style={{ display: "flex", alignItems: "center", gap: 5 }}
              >
                <Download size={12} />
                {creatingBackup === algo ? "Criando..." : algo.toUpperCase()}
              </button>
            ))}
          </div>
        </div>

        {backups.length > 0 && (
          <div className="card" style={{ overflow: "hidden" }}>
            {restoreSuccess && (
              <div style={{
                padding: "10px 16px",
                background: "var(--green-tint)",
                borderBottom: "1px solid var(--border)",
                display: "flex",
                alignItems: "center",
                gap: 8,
                fontSize: 12,
                color: "var(--green)",
                fontWeight: 600,
              }}>
                <CheckCircle2 size={14} />
                Backup restaurado com sucesso: {restoreSuccess}
              </div>
            )}
            <div style={{ maxHeight: 260, overflowY: "auto" }}>
              {backups.map((b, i) => (
                <div
                  key={b.arquivo}
                  style={{
                    display: "flex",
                    alignItems: "center",
                    gap: 12,
                    padding: "11px 16px",
                    borderBottom: i < backups.length - 1 ? "1px solid var(--border)" : "none",
                    background: restoringFile === b.arquivo ? "var(--canvas)" : "transparent",
                  }}
                >
                  <FileArchive size={15} style={{ color: "var(--ink-4)", flexShrink: 0 }} />
                  <div style={{ flex: 1, minWidth: 0 }}>
                    <div style={{
                      fontSize: 12,
                      fontWeight: 600,
                      color: "var(--ink)",
                      overflow: "hidden",
                      textOverflow: "ellipsis",
                      whiteSpace: "nowrap",
                    }}>
                      {b.arquivo}
                    </div>
                    <div style={{ fontSize: 11, color: "var(--ink-3)", display: "flex", alignItems: "center", gap: 8, marginTop: 2 }}>
                      <span style={{
                        padding: "1px 5px",
                        borderRadius: 99,
                        background: "var(--accent-tint)",
                        color: "var(--accent)",
                        fontWeight: 700,
                        fontSize: 9,
                        textTransform: "uppercase",
                      }}>
                        {b.algoritmo}
                      </span>
                      <span>{formatBytes(b.tamanho)}</span>
                      <span style={{ display: "flex", alignItems: "center", gap: 3 }}>
                        <Clock size={10} /> {b.criadoEm}
                      </span>
                    </div>
                  </div>
                  <button
                    onClick={() => handleRestore(b.arquivo)}
                    disabled={restoringFile !== null || creatingBackup !== null}
                    className="btn btn-secondary btn-sm"
                    style={{ display: "flex", alignItems: "center", gap: 5, flexShrink: 0, color: "var(--amber)" }}
                    title="Restaurar este backup"
                  >
                    {restoringFile === b.arquivo
                      ? <><RotateCcw size={11} className="anim-spin" /> Restaurando...</>
                      : <><RotateCcw size={11} /> Restaurar</>
                    }
                  </button>
                </div>
              ))}
            </div>
          </div>
        )}
      </div>

      <div
        style={{
          marginTop: 16,
          padding: "18px 24px",
          borderRadius: "var(--radius-xl)",
          background: "var(--canvas)",
          border: "1px solid var(--border)",
          display: "flex",
          alignItems: "center",
          gap: 16,
        }}
      >
        <div style={{ fontSize: 13, color: "var(--ink-3)", flex: 1 }}>
          Explore o mapa da plataforma para ver a distribuição geográfica dos imóveis.
        </div>
        <button
          onClick={() => navigate("/explore")}
          className="btn btn-secondary btn-sm"
          style={{ flexShrink: 0 }}
        >
          Ver mapa <ArrowRight size={12} />
        </button>
      </div>
    </div>
  );
}

function BigKpi({ label, value, icon, color, isText }: { label: string; value: string; icon: React.ReactNode; color: string; isText?: boolean }) {
  return (
    <div
      style={{
        padding: "24px",
        borderRadius: "var(--radius-lg)",
        border: "1px solid var(--border)",
        background: "var(--surface)",
        position: "relative",
        overflow: "hidden",
      }}
    >
      <div style={{ position: "absolute", top: -10, right: -10, opacity: 0.06, color }}>
        <span style={{ fontSize: 80 }}>{icon}</span>
      </div>
      <div style={{ display: "flex", alignItems: "center", gap: 10, marginBottom: 16 }}>
        <div style={{ width: 32, height: 32, borderRadius: "var(--radius-xs)", background: `${color}18`, color, display: "flex", alignItems: "center", justifyContent: "center" }}>
          {icon}
        </div>
      </div>
      <div style={{ fontSize: isText ? 20 : 32, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.05em", marginBottom: 4 }}>
        {value}
      </div>
      <div style={{ fontSize: 12, color: "var(--ink-3)", fontWeight: 500 }}>{label}</div>
    </div>
  );
}
