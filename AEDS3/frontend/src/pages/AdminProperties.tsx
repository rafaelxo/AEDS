import { useEffect, useState, useCallback } from "react";
import { Search, Building2, MapPin, Trash2, Eye } from "lucide-react";
import { imoveisService, usuarioService, type Imovel } from "../services/api";

function abbrevName(name: string): string {
  const parts = name.trim().split(/\s+/);
  if (parts.length <= 1 || name.length <= 18) return name;
  return parts[0] + " " + parts.slice(1).map((p) => p[0] + ".").join(" ");
}
function imovelCode(id: number): string {
  return "IMO-" + id.toString(36).toUpperCase().padStart(3, "0");
}
import { useStore } from "../app/store";

function fmt(v: number) {
  return v.toLocaleString("pt-BR", { style: "currency", currency: "BRL", maximumFractionDigits: 0 });
}

export default function AdminProperties() {
  const { openDetail } = useStore();
  const [properties, setProperties] = useState<Imovel[]>([]);
  const [loading, setLoading] = useState(true);
  const [search, setSearch] = useState("");
  const [deleting, setDeleting] = useState<number | null>(null);
  const [hostMap, setHostMap] = useState<Record<number, string>>({});

  const fetch = useCallback(async () => {
    setLoading(true);
    try {
      const [data, users] = await Promise.all([
        imoveisService.getAll(search ? { busca: search } : undefined),
        usuarioService.getAll(),
      ]);
      setProperties(data);
      setHostMap(Object.fromEntries(users.map((u) => [u.idUsuario, u.nome])));
    } finally {
      setLoading(false);
    }
  }, [search]);

  useEffect(() => { fetch(); }, [fetch]);

  const handleDelete = async (p: Imovel) => {
    if (!confirm(`Excluir "${p.titulo}"?`)) return;
    setDeleting(p.idImovel);
    try {
      await imoveisService.delete(p.idImovel);
      setProperties((prev) => prev.filter((x) => x.idImovel !== p.idImovel));
    } catch (e) {
      alert(e instanceof Error ? e.message : "Erro ao excluir");
    } finally {
      setDeleting(null);
    }
  };

  const handleToggle = async (p: Imovel) => {
    try {
      const updated = await imoveisService.update(p.idImovel, { ativo: !p.ativo });
      setProperties((prev) => prev.map((x) => x.idImovel === p.idImovel ? updated : x));
    } catch (e) {
      alert(e instanceof Error ? e.message : "Erro ao atualizar");
    }
  };

  return (
    <div style={{ padding: "28px 36px" }}>
      <div style={{ display: "flex", alignItems: "center", justifyContent: "space-between", marginBottom: 24 }}>
        <div>
          <h1 style={{ fontSize: 22, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.04em", margin: "0 0 4px" }}>Imóveis</h1>
          <p style={{ fontSize: 13, color: "var(--ink-3)", margin: 0 }}>{properties.length} imóvel(is) na plataforma</p>
        </div>
        <div style={{ position: "relative" }}>
          <Search size={14} style={{ position: "absolute", left: 12, top: "50%", transform: "translateY(-50%)", color: "var(--ink-4)", pointerEvents: "none" }} />
          <input className="field-input" style={{ paddingLeft: 34 }} placeholder="Buscar imóvel..." value={search} onChange={(e) => setSearch(e.target.value)} />
        </div>
      </div>

      <div className="card" style={{ overflow: "hidden" }}>
        {loading ? (
          <div style={{ padding: 40, textAlign: "center" }}>
            <div className="anim-spin" style={{ width: 24, height: 24, border: "3px solid var(--border)", borderTopColor: "var(--accent)", borderRadius: "50%", margin: "0 auto" }} />
          </div>
        ) : properties.length === 0 ? (
          <div style={{ padding: 48, textAlign: "center" }}>
            <Building2 size={36} style={{ color: "var(--ink-5)", margin: "0 auto 12px" }} />
            <p style={{ fontSize: 14, color: "var(--ink-3)", margin: 0 }}>Nenhum imóvel encontrado.</p>
          </div>
        ) : (
          <table className="data-table">
            <thead>
              <tr>
                <th>#</th>
                <th>Imóvel</th>
                <th>Cidade</th>
                <th>Anfitrião</th>
                <th>Diária</th>
                <th>Status</th>
                <th style={{ textAlign: "right" }}>Ações</th>
              </tr>
            </thead>
            <tbody>
              {properties.map((p) => (
                <tr key={p.idImovel}>
                  <td style={{ fontSize: 11, color: "var(--ink-4)", fontFamily: "monospace", fontWeight: 600, letterSpacing: "0.04em", whiteSpace: "nowrap" }}>{imovelCode(p.idImovel)}</td>
                  <td>
                    <div style={{ display: "flex", alignItems: "center", gap: 10 }}>
                      {p.fotos?.[0] ? (
                        <img src={p.fotos[0]} alt="" style={{ width: 40, height: 40, borderRadius: "var(--radius-sm)", objectFit: "cover", flexShrink: 0 }} />
                      ) : (
                        <div style={{ width: 40, height: 40, borderRadius: "var(--radius-sm)", background: "var(--canvas)", display: "flex", alignItems: "center", justifyContent: "center", flexShrink: 0 }}>
                          <Building2 size={16} style={{ color: "var(--ink-5)" }} />
                        </div>
                      )}
                      <span style={{ fontSize: 13, fontWeight: 600, color: "var(--ink)", maxWidth: 200, overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap", display: "block" }}>
                        {p.titulo}
                      </span>
                    </div>
                  </td>
                  <td style={{ fontSize: 12 }}>
                    <div style={{ display: "flex", alignItems: "center", gap: 4, color: "var(--ink-2)" }}>
                      <MapPin size={11} /> {p.cidade}
                    </div>
                  </td>
                  <td style={{ fontSize: 12, color: "var(--ink-2)" }}>{abbrevName(hostMap[p.idUsuario] ?? "#" + p.idUsuario)}</td>
                  <td style={{ fontSize: 13, fontWeight: 600 }}>{fmt(p.valorDiaria)}</td>
                  <td>
                    <button
                      onClick={() => handleToggle(p)}
                      className={`badge ${p.ativo ? "badge-green" : "badge-ink"}`}
                      style={{ border: "none", cursor: "pointer" }}
                    >
                      {p.ativo ? "Ativo" : "Inativo"}
                    </button>
                  </td>
                  <td style={{ textAlign: "right" }}>
                    <div style={{ display: "flex", gap: 6, justifyContent: "flex-end" }}>
                      <button onClick={() => openDetail(p.idImovel)} className="btn btn-ghost btn-sm" style={{ display: "flex", alignItems: "center", gap: 4 }}>
                        <Eye size={13} /> Ver
                      </button>
                      <button onClick={() => handleDelete(p)} disabled={deleting === p.idImovel}
                        style={{ padding: "6px 10px", borderRadius: "var(--radius-sm)", border: "none", background: "var(--red-tint)", color: "var(--red)", display: "flex", alignItems: "center" }}>
                        {deleting === p.idImovel ? "..." : <Trash2 size={13} />}
                      </button>
                    </div>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        )}
      </div>
    </div>
  );
}
