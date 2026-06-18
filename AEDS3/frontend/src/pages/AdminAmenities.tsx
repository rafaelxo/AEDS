import { useEffect, useState, useCallback } from "react";
import { Plus, Sparkles, Edit2, Trash2, ChevronLeft } from "lucide-react";
import { comodidadeService, type ComodidadeCatalogo, type CreateComodidadeInput } from "../services/api";

type View = "list" | "form";
interface FormState {
  nome: string;
  descricao: string;
  icone: string;
  ativo: boolean;
}
const EMPTY: FormState = { nome: "", descricao: "", icone: "", ativo: true };

export default function AdminAmenities() {
  const [view, setView] = useState<View>("list");
  const [items, setItems] = useState<ComodidadeCatalogo[]>([]);
  const [loading, setLoading] = useState(true);
  const [editing, setEditing] = useState<ComodidadeCatalogo | null>(null);
  const [form, setForm] = useState<FormState>(EMPTY);
  const [submitting, setSubmitting] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [deleting, setDeleting] = useState<number | null>(null);

  const fetch = useCallback(async () => {
    setLoading(true);
    try {
      const data = await comodidadeService.getAll();
      setItems(data);
    } finally {
      setLoading(false);
    }
  }, []);

  useEffect(() => { fetch(); }, [fetch]);

  const openNew = () => { setEditing(null); setForm(EMPTY); setError(null); setView("form"); };
  const openEdit = (c: ComodidadeCatalogo) => {
    setEditing(c);
    setForm({ nome: c.nome, descricao: c.descricao ?? "", icone: c.icone ?? "", ativo: c.ativo });
    setError(null);
    setView("form");
  };

  const handleDelete = async (c: ComodidadeCatalogo) => {
    if (!confirm(`Excluir "${c.nome}"?`)) return;
    setDeleting(c.idComodidade);
    try {
      await comodidadeService.delete(c.idComodidade);
      setItems((prev) => prev.filter((x) => x.idComodidade !== c.idComodidade));
    } catch (e) {
      alert(e instanceof Error ? e.message : "Erro ao excluir");
    } finally {
      setDeleting(null);
    }
  };

  const handleToggle = async (c: ComodidadeCatalogo) => {
    try {
      const updated = await comodidadeService.update(c.idComodidade, { ativo: !c.ativo });
      setItems((prev) => prev.map((x) => x.idComodidade === c.idComodidade ? updated : x));
    } catch (e) {
      alert(e instanceof Error ? e.message : "Erro");
    }
  };

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setSubmitting(true);
    setError(null);
    try {
      const payload: CreateComodidadeInput = { nome: form.nome, descricao: form.descricao || undefined, icone: form.icone || undefined, ativo: editing ? form.ativo : true };
      if (editing) {
        await comodidadeService.update(editing.idComodidade, payload);
      } else {
        await comodidadeService.create(payload);
      }
      await fetch();
      setView("list");
    } catch (e) {
      setError(e instanceof Error ? e.message : "Erro ao salvar");
    } finally {
      setSubmitting(false);
    }
  };

  if (view === "form") {
    const initial = form.nome.trim()[0]?.toUpperCase() ?? "";

    return (
      <div style={{ padding: "28px 36px", width: 600, margin: "0 auto" }}>
        <div style={{ display: "flex", alignItems: "center", gap: 12, marginBottom: 24 }}>
          <button
            onClick={() => setView("list")}
            style={{ background: "none", border: "none", color: "var(--ink-3)", fontSize: 13, fontWeight: 600, display: "flex", alignItems: "center", gap: 4, padding: 0, cursor: "pointer" }}
          >
            <ChevronLeft size={16} /> Voltar
          </button>
          <div style={{ width: 1, height: 16, background: "var(--border)" }} />
          <h1 style={{ fontSize: 20, fontWeight: 800, color: "var(--ink)", margin: 0 }}>
            {editing ? "Editar comodidade" : "Nova comodidade"}
          </h1>
        </div>

        <form
          onSubmit={handleSubmit}
          style={{ background: "var(--surface)", border: "1px solid var(--border)", borderRadius: "var(--radius-lg)", boxShadow: "var(--shadow-md)", overflow: "hidden" }}
        >
          <div style={{ padding: "20px 24px", background: "linear-gradient(130deg, #F0F7FF 0%, var(--surface) 65%)", borderBottom: "1px solid var(--border)", display: "flex", alignItems: "center", gap: 16 }}>
            <div style={{
              width: 52, height: 52, borderRadius: "var(--radius-md)",
              background: initial ? "var(--accent-tint)" : "var(--canvas)",
              border: `1.5px solid ${initial ? "var(--accent-mid)" : "var(--border)"}`,
              display: "flex", alignItems: "center", justifyContent: "center",
              flexShrink: 0, transition: "all 200ms ease",
            }}>
              {form.icone ? (
                <span style={{ fontSize: 10, fontWeight: 800, color: "var(--accent)", fontFamily: "monospace", letterSpacing: "-0.03em", textAlign: "center", lineHeight: 1.2, padding: "0 4px" }}>
                  {form.icone.slice(0, 5)}
                </span>
              ) : initial ? (
                <span style={{ fontSize: 22, fontWeight: 800, color: "var(--accent)" }}>{initial}</span>
              ) : (
                <Sparkles size={20} style={{ color: "var(--ink-5)" }} />
              )}
            </div>
            <div style={{ flex: 1, minWidth: 0 }}>
              <div style={{ fontSize: 16, fontWeight: 700, color: "var(--ink)", overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap", minHeight: 22 }}>
                {form.nome || <span style={{ color: "var(--ink-4)", fontWeight: 400 }}>Nome da comodidade</span>}
              </div>
              {form.descricao && (
                <div style={{ fontSize: 12, color: "var(--ink-3)", marginTop: 4, overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap" }}>
                  {form.descricao}
                </div>
              )}
              {!form.descricao && form.icone && (
                <div style={{ marginTop: 5 }}>
                  <span style={{ fontSize: 10, fontWeight: 700, fontFamily: "monospace", color: "var(--accent)", background: "var(--accent-tint)", padding: "2px 8px", borderRadius: 4 }}>
                    {form.icone}
                  </span>
                </div>
              )}
            </div>
          </div>

          <div style={{ padding: "24px", display: "flex", flexDirection: "column", gap: 18 }}>

            <AmenitySection>Identificação</AmenitySection>

            <div>
              <AmenityLabel>Nome *</AmenityLabel>
              <input
                className="field-input"
                value={form.nome}
                onChange={(e) => setForm((f) => ({ ...f, nome: e.target.value }))}
                required
                minLength={2}
                placeholder="Ex: Wi-Fi, Piscina, Academia..."
                style={{ fontSize: 15, fontWeight: 600 }}
              />
            </div>

            <div>
              <AmenityLabel>Ícone (slug)</AmenityLabel>
              <div style={{ position: "relative" }}>
                <input
                  className="field-input"
                  value={form.icone}
                  onChange={(e) => setForm((f) => ({ ...f, icone: e.target.value }))}
                  placeholder="wifi, pool, gym, parking..."
                  style={{ paddingRight: form.icone ? 72 : 14, fontFamily: "monospace" }}
                />
                {form.icone && (
                  <span style={{
                    position: "absolute", right: 10, top: "50%", transform: "translateY(-50%)",
                    fontSize: 10, fontWeight: 700, fontFamily: "monospace",
                    color: "var(--accent)", background: "var(--accent-tint)",
                    padding: "3px 8px", borderRadius: 4, pointerEvents: "none",
                    maxWidth: 60, overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap",
                  }}>
                    {form.icone}
                  </span>
                )}
              </div>
              <p style={{ fontSize: 11, color: "var(--ink-4)", margin: "5px 0 0" }}>
                Slug de referência para exibição no frontend
              </p>
            </div>

            <AmenitySection>Descrição</AmenitySection>

            <div>
              <div style={{ display: "flex", justifyContent: "space-between", alignItems: "baseline", marginBottom: 6 }}>
                <AmenityLabel>Descrição</AmenityLabel>
                <span style={{ fontSize: 10, color: form.descricao.length > 180 ? "var(--amber)" : "var(--ink-5)", fontWeight: 600 }}>
                  {form.descricao.length}/200
                </span>
              </div>
              <textarea
                className="field-input"
                rows={3}
                value={form.descricao}
                maxLength={200}
                onChange={(e) => setForm((f) => ({ ...f, descricao: e.target.value }))}
                placeholder="Breve descrição da comodidade..."
                style={{ resize: "none", lineHeight: 1.6 }}
              />
            </div>

            {editing && (
              <>
                <AmenitySection>Disponibilidade</AmenitySection>
                <div style={{
                  display: "flex", alignItems: "center", justifyContent: "space-between",
                  padding: "14px 16px", background: "var(--canvas)",
                  borderRadius: "var(--radius-md)", border: "1.5px solid var(--border)",
                }}>
                  <div>
                    <div style={{ fontSize: 13, fontWeight: 600, color: "var(--ink)" }}>Comodidade ativa</div>
                    <div style={{ fontSize: 11, color: "var(--ink-4)", marginTop: 2 }}>Visível nos imóveis do catálogo</div>
                  </div>
                  <button
                    type="button"
                    onClick={() => setForm((f) => ({ ...f, ativo: !f.ativo }))}
                    style={{
                      width: 44, height: 24, borderRadius: 99, border: "none",
                      background: form.ativo ? "var(--accent)" : "var(--ink-5)",
                      position: "relative", transition: "background 220ms ease",
                      cursor: "pointer", flexShrink: 0,
                    }}
                  >
                    <span style={{
                      position: "absolute", top: 3,
                      left: form.ativo ? 23 : 3,
                      width: 18, height: 18, borderRadius: "50%",
                      background: "#fff", transition: "left 220ms ease",
                      boxShadow: "0 1px 4px rgba(0,0,0,0.18)", display: "block",
                    }} />
                  </button>
                </div>
              </>
            )}

            {error && (
              <div style={{ padding: "10px 14px", borderRadius: "var(--radius-md)", background: "var(--red-tint)", color: "var(--red)", fontSize: 13, fontWeight: 500 }}>
                {error}
              </div>
            )}

            <div style={{ display: "flex", gap: 10, justifyContent: "flex-end", paddingTop: 8, borderTop: "1px solid var(--border)", marginTop: 2 }}>
              <button type="button" onClick={() => setView("list")} className="btn btn-secondary">Cancelar</button>
              <button type="submit" disabled={submitting} className="btn btn-primary">
                {submitting ? "Salvando..." : editing ? "Salvar alterações" : "Criar comodidade"}
              </button>
            </div>
          </div>
        </form>
      </div>
    );
  }

  return (
    <div style={{ padding: "28px 36px" }}>
      <div style={{ display: "flex", alignItems: "center", justifyContent: "space-between", marginBottom: 24 }}>
        <div>
          <h1 style={{ fontSize: 22, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.04em", margin: "0 0 4px" }}>Comodidades</h1>
          <p style={{ fontSize: 13, color: "var(--ink-3)", margin: 0 }}>{items.length} comodidade(s) no catálogo</p>
        </div>
        <button onClick={openNew} className="btn btn-primary"><Plus size={14} /> Nova comodidade</button>
      </div>

      {loading ? (
        <div style={{ display: "grid", gridTemplateColumns: "repeat(auto-fill, minmax(220px, 1fr))", gap: 12 }}>
          {[1, 2, 3, 4, 5, 6].map((i) => <div key={i} style={{ height: 100, borderRadius: "var(--radius-lg)", background: "var(--canvas)" }} />)}
        </div>
      ) : items.length === 0 ? (
        <div style={{ padding: 64, textAlign: "center" }}>
          <Sparkles size={40} style={{ color: "var(--ink-5)", margin: "0 auto 12px" }} />
          <p style={{ fontSize: 14, color: "var(--ink-3)", margin: "0 0 16px" }}>Nenhuma comodidade cadastrada.</p>
          <button onClick={openNew} className="btn btn-primary btn-sm"><Plus size={13} /> Criar primeira</button>
        </div>
      ) : (
        <div style={{ display: "grid", gridTemplateColumns: "repeat(auto-fill, minmax(220px, 1fr))", gap: 12 }}>
          {items.map((c) => (
            <div key={c.idComodidade} className="card" style={{ padding: "16px 18px" }}>
              <div style={{ display: "flex", alignItems: "flex-start", justifyContent: "space-between", marginBottom: 8 }}>
                <div>
                  <div style={{ fontSize: 14, fontWeight: 700, color: "var(--ink)", marginBottom: 3 }}>{c.nome}</div>
                  {c.icone && <div style={{ fontSize: 11, color: "var(--ink-4)", fontFamily: "monospace" }}>{c.icone}</div>}
                </div>
                <button
                  onClick={() => handleToggle(c)}
                  className={`badge ${c.ativo ? "badge-green" : "badge-ink"}`}
                  style={{ border: "none", cursor: "pointer", flexShrink: 0 }}
                >
                  {c.ativo ? "Ativa" : "Inativa"}
                </button>
              </div>
              {c.descricao && <p style={{ fontSize: 12, color: "var(--ink-3)", margin: "0 0 12px", lineHeight: 1.5 }}>{c.descricao}</p>}
              <div style={{ display: "flex", gap: 6, borderTop: "1px solid var(--border)", paddingTop: 10 }}>
                <button onClick={() => openEdit(c)} className="btn btn-ghost btn-sm" style={{ display: "flex", alignItems: "center", gap: 4 }}>
                  <Edit2 size={12} /> Editar
                </button>
                <button onClick={() => handleDelete(c)} disabled={deleting === c.idComodidade}
                  style={{ padding: "5px 10px", borderRadius: "var(--radius-sm)", border: "none", background: "var(--red-tint)", color: "var(--red)", display: "flex", alignItems: "center", gap: 4, fontSize: 12 }}>
                  {deleting === c.idComodidade ? "..." : <><Trash2 size={12} /></>}
                </button>
              </div>
            </div>
          ))}
        </div>
      )}
    </div>
  );
}

function AmenitySection({ children }: { children: React.ReactNode }) {
  return (
    <div style={{ display: "flex", alignItems: "center", gap: 10, margin: "2px 0" }}>
      <div style={{ width: 3, height: 12, background: "var(--accent)", borderRadius: 2, flexShrink: 0 }} />
      <span style={{ fontSize: 10, fontWeight: 700, letterSpacing: "0.08em", color: "var(--ink-4)", textTransform: "uppercase", whiteSpace: "nowrap" }}>
        {children}
      </span>
      <div style={{ height: 1, flex: 1, background: "var(--border)" }} />
    </div>
  );
}

function AmenityLabel({ children }: { children: React.ReactNode }) {
  return (
    <label style={{ fontSize: 11, fontWeight: 700, color: "var(--ink-3)", display: "block", marginBottom: 6, letterSpacing: "0.02em" }}>
      {children}
    </label>
  );
}
