import { useEffect, useState, useCallback } from "react";
import { Search, Plus, Edit2, Trash2, Users, Eye, EyeOff, User } from "lucide-react";
import { usuarioService, type Usuario, type CreateUsuarioInput } from "../services/api";

function statusInfo(tipo: string) {
  if (tipo === "ADMIN") return { label: "Admin", cls: "badge-red" };
  if (tipo === "ANFITRIAO") return { label: "Anfitrião", cls: "badge-blue" };
  return { label: "Hóspede", cls: "badge-ink" };
}

type View = "list" | "form";
interface FormState {
  nome: string;
  email: string;
  telefone: string;
  senha: string;
  tipo: Usuario["tipo"];
  ativo: boolean;
}
const EMPTY_FORM: FormState = { nome: "", email: "", telefone: "", senha: "", tipo: "HOSPEDE", ativo: true };

const ROLE_META = {
  HOSPEDE:   { label: "Hóspede",   bg: "var(--blue-tint)",  text: "var(--blue)"  },
  ANFITRIAO: { label: "Anfitrião", bg: "var(--green-tint)", text: "var(--green)" },
  ADMIN:     { label: "Admin",     bg: "var(--red-tint)",   text: "var(--red)"   },
} as const;

export default function AdminUsers() {
  const [view, setView] = useState<View>("list");
  const [users, setUsers] = useState<Usuario[]>([]);
  const [loading, setLoading] = useState(true);
  const [search, setSearch] = useState("");
  const [searchInput, setSearchInput] = useState("");
  const [editing, setEditing] = useState<Usuario | null>(null);
  const [form, setForm] = useState<FormState>(EMPTY_FORM);
  const [submitting, setSubmitting] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [deleting, setDeleting] = useState<number | null>(null);
  const [showPw, setShowPw] = useState(false);

  const fetch = useCallback(async () => {
    setLoading(true);
    try {
      const data = await usuarioService.getAll(search ? { busca: search } : undefined);
      setUsers(data);
    } finally {
      setLoading(false);
    }
  }, [search]);

  useEffect(() => { fetch(); }, [fetch]);

  useEffect(() => {
    const t = setTimeout(() => setSearch(searchInput), 400);
    return () => clearTimeout(t);
  }, [searchInput]);

  const openNew = () => {
    setEditing(null);
    setForm(EMPTY_FORM);
    setError(null);
    setShowPw(false);
    setView("form");
  };

  const openEdit = (u: Usuario) => {
    setEditing(u);
    setForm({ nome: u.nome, email: u.email, telefone: u.telefone ?? "", senha: "", tipo: u.tipo, ativo: u.ativo });
    setError(null);
    setShowPw(false);
    setView("form");
  };

  const handleDelete = async (u: Usuario) => {
    if (!confirm(`Excluir "${u.nome}"?`)) return;
    setDeleting(u.idUsuario);
    try {
      await usuarioService.delete(u.idUsuario);
      setUsers((prev) => prev.filter((x) => x.idUsuario !== u.idUsuario));
    } catch (e) {
      alert(e instanceof Error ? e.message : "Erro ao excluir");
    } finally {
      setDeleting(null);
    }
  };

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setSubmitting(true);
    setError(null);
    try {
      const payload: CreateUsuarioInput = {
        nome: form.nome,
        email: form.email,
        telefone: form.telefone || undefined,
        tipo: form.tipo,
        ativo: editing ? form.ativo : true,
        ...(form.senha ? { senha: form.senha } : {}),
      };
      if (editing) {
        await usuarioService.update(editing.idUsuario, payload);
      } else {
        await usuarioService.create(payload);
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
    const initials = form.nome.trim().split(/\s+/).filter(Boolean).map((n) => n[0]?.toUpperCase() ?? "").slice(0, 2).join("");
    const role = ROLE_META[form.tipo];

    return (
      <div style={{ padding: "28px 36px", width: 600, margin: "0 auto" }}>
        <div style={{ display: "flex", alignItems: "center", gap: 12, marginBottom: 24 }}>
          <button
            onClick={() => setView("list")}
            style={{ background: "none", border: "none", color: "var(--ink-3)", fontSize: 13, fontWeight: 600, display: "flex", alignItems: "center", gap: 4, padding: 0, cursor: "pointer" }}
          >
            ← Voltar
          </button>
          <div style={{ width: 1, height: 16, background: "var(--border)" }} />
          <h1 style={{ fontSize: 20, fontWeight: 800, color: "var(--ink)", margin: 0 }}>
            {editing ? "Editar usuário" : "Novo usuário"}
          </h1>
        </div>

        <form
          onSubmit={handleSubmit}
          style={{ background: "var(--surface)", border: "1px solid var(--border)", borderRadius: "var(--radius-lg)", boxShadow: "var(--shadow-md)", overflow: "hidden" }}
        >
          <div style={{ padding: "20px 24px", background: "linear-gradient(130deg, var(--accent-tint) 0%, var(--surface) 65%)", borderBottom: "1px solid var(--border)", display: "flex", alignItems: "center", gap: 16 }}>
            <div style={{
              width: 52, height: 52, borderRadius: "50%",
              background: initials ? "var(--accent)" : "var(--ink-5)",
              color: "#fff", display: "flex", alignItems: "center", justifyContent: "center",
              fontWeight: 800, fontSize: initials ? 18 : 20, flexShrink: 0,
              letterSpacing: "-0.02em", transition: "background 200ms ease",
              boxShadow: initials ? "0 2px 12px rgba(200,92,50,0.28)" : "none",
            }}>
              {initials || <User size={22} />}
            </div>
            <div style={{ flex: 1, minWidth: 0 }}>
              <div style={{ fontSize: 16, fontWeight: 700, color: "var(--ink)", overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap", minHeight: 22 }}>
                {form.nome || <span style={{ color: "var(--ink-4)", fontWeight: 400 }}>Nome do usuário</span>}
              </div>
              <div style={{ marginTop: 6 }}>
                <span style={{
                  fontSize: 11, fontWeight: 700, padding: "3px 10px", borderRadius: 99,
                  background: role.bg, color: role.text, display: "inline-block",
                  transition: "all 180ms ease",
                }}>
                  {role.label}
                </span>
              </div>
            </div>
          </div>

          <div style={{ padding: "24px", display: "flex", flexDirection: "column", gap: 18 }}>

            <SectionDivider>Dados pessoais</SectionDivider>

            <div>
              <FieldLabel>Nome completo *</FieldLabel>
              <input
                className="field-input"
                value={form.nome}
                onChange={(e) => setForm((f) => ({ ...f, nome: e.target.value }))}
                required
                placeholder="Ex: João Silva"
              />
            </div>

            <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 12 }}>
              <div>
                <FieldLabel>Email *</FieldLabel>
                <input
                  className="field-input"
                  type="email"
                  value={form.email}
                  onChange={(e) => setForm((f) => ({ ...f, email: e.target.value }))}
                  required
                  placeholder="email@exemplo.com"
                />
              </div>
              <div>
                <FieldLabel>Telefone</FieldLabel>
                <input
                  className="field-input"
                  value={form.telefone}
                  onChange={(e) => setForm((f) => ({ ...f, telefone: e.target.value }))}
                  placeholder="(00) 00000-0000"
                />
              </div>
            </div>

            <SectionDivider>Credenciais</SectionDivider>

            <div>
              <FieldLabel>{editing ? "Senha — deixe vazio para manter" : "Senha *"}</FieldLabel>
              <div style={{ position: "relative" }}>
                <input
                  className="field-input"
                  type={showPw ? "text" : "password"}
                  value={form.senha}
                  onChange={(e) => setForm((f) => ({ ...f, senha: e.target.value }))}
                  required={!editing}
                  style={{ paddingRight: 44 }}
                  placeholder="••••••••"
                />
                <button
                  type="button"
                  onClick={() => setShowPw((v) => !v)}
                  style={{ position: "absolute", right: 12, top: "50%", transform: "translateY(-50%)", background: "none", border: "none", color: "var(--ink-4)", display: "flex", padding: 4, cursor: "pointer" }}
                >
                  {showPw ? <EyeOff size={15} /> : <Eye size={15} />}
                </button>
              </div>
            </div>

            <SectionDivider>Perfil de acesso</SectionDivider>

            <div style={{ display: "flex", gap: 8 }}>
              {(["HOSPEDE", "ANFITRIAO", "ADMIN"] as const).map((t) => {
                const active = form.tipo === t;
                const meta = ROLE_META[t];
                return (
                  <button
                    key={t}
                    type="button"
                    onClick={() => setForm((f) => ({ ...f, tipo: t }))}
                    style={{
                      flex: 1, padding: "11px 8px", borderRadius: "var(--radius-md)",
                      border: `1.5px solid ${active ? meta.text : "var(--border)"}`,
                      background: active ? meta.bg : "transparent",
                      color: active ? meta.text : "var(--ink-3)",
                      fontWeight: 700, fontSize: 12, cursor: "pointer",
                      transition: "all 150ms ease",
                    }}
                  >
                    {meta.label}
                  </button>
                );
              })}
            </div>

            {editing && (
              <div style={{
                display: "flex", alignItems: "center", justifyContent: "space-between",
                padding: "14px 16px", background: "var(--canvas)",
                borderRadius: "var(--radius-md)", border: "1.5px solid var(--border)",
              }}>
                <div>
                  <div style={{ fontSize: 13, fontWeight: 600, color: "var(--ink)" }}>Conta ativa</div>
                  <div style={{ fontSize: 11, color: "var(--ink-4)", marginTop: 2 }}>Permite acesso ao sistema</div>
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
            )}

            {error && (
              <div style={{ padding: "10px 14px", borderRadius: "var(--radius-md)", background: "var(--red-tint)", color: "var(--red)", fontSize: 13, fontWeight: 500 }}>
                {error}
              </div>
            )}

            <div style={{ display: "flex", gap: 10, justifyContent: "flex-end", paddingTop: 8, borderTop: "1px solid var(--border)", marginTop: 2 }}>
              <button type="button" onClick={() => setView("list")} className="btn btn-secondary">Cancelar</button>
              <button type="submit" disabled={submitting} className="btn btn-primary">
                {submitting ? "Salvando..." : editing ? "Salvar alterações" : "Criar usuário"}
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
          <h1 style={{ fontSize: 22, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.04em", margin: "0 0 4px" }}>Usuários</h1>
          <p style={{ fontSize: 13, color: "var(--ink-3)", margin: 0 }}>{users.length} usuário(s)</p>
        </div>
        <div style={{ display: "flex", gap: 10 }}>
          <div style={{ position: "relative" }}>
            <Search size={14} style={{ position: "absolute", left: 12, top: "50%", transform: "translateY(-50%)", color: "var(--ink-4)", pointerEvents: "none" }} />
            <input className="field-input" style={{ paddingLeft: 34 }} placeholder="Buscar usuário..." value={searchInput} onChange={(e) => setSearchInput(e.target.value)} />
          </div>
          <button onClick={openNew} className="btn btn-primary"><Plus size={14} /> Novo usuário</button>
        </div>
      </div>

      <div className="card" style={{ overflow: "hidden" }}>
        {loading ? (
          <div style={{ padding: 40, textAlign: "center" }}>
            <div className="anim-spin" style={{ width: 24, height: 24, border: "3px solid var(--border)", borderTopColor: "var(--accent)", borderRadius: "50%", margin: "0 auto" }} />
          </div>
        ) : users.length === 0 ? (
          <div style={{ padding: 48, textAlign: "center" }}>
            <Users size={36} style={{ color: "var(--ink-5)", margin: "0 auto 12px" }} />
            <p style={{ fontSize: 14, color: "var(--ink-3)", margin: 0 }}>Nenhum usuário encontrado.</p>
          </div>
        ) : (
          <table className="data-table">
            <thead>
              <tr>
                <th>Usuário</th>
                <th>Email</th>
                <th>Tipo</th>
                <th>Status</th>
                <th style={{ textAlign: "right" }}>Ações</th>
              </tr>
            </thead>
            <tbody>
              {users.map((u) => {
                const { label, cls } = statusInfo(u.tipo);
                const initials = u.nome.split(" ").map((n) => n[0]).slice(0, 2).join("").toUpperCase();
                return (
                  <tr key={u.idUsuario}>
                    <td>
                      <div style={{ display: "flex", alignItems: "center", gap: 10 }}>
                        <div style={{ width: 32, height: 32, borderRadius: "50%", background: "var(--accent-tint)", color: "var(--accent)", display: "flex", alignItems: "center", justifyContent: "center", fontWeight: 700, fontSize: 11, flexShrink: 0 }}>
                          {initials}
                        </div>
                        <div>
                          <div style={{ fontSize: 13, fontWeight: 600, color: "var(--ink)" }}>{u.nome}</div>
                          {u.telefone && <div style={{ fontSize: 11, color: "var(--ink-3)" }}>{u.telefone}</div>}
                        </div>
                      </div>
                    </td>
                    <td style={{ fontSize: 12 }}>{u.email}</td>
                    <td><span className={`badge ${cls}`}>{label}</span></td>
                    <td><span className={`badge ${u.ativo ? "badge-green" : "badge-ink"}`}>{u.ativo ? "Ativo" : "Inativo"}</span></td>
                    <td style={{ textAlign: "right" }}>
                      <div style={{ display: "flex", gap: 6, justifyContent: "flex-end" }}>
                        <button onClick={() => openEdit(u)} className="btn btn-ghost btn-sm" style={{ display: "flex", alignItems: "center", gap: 4 }}>
                          <Edit2 size={13} /> Editar
                        </button>
                        <button onClick={() => handleDelete(u)} disabled={deleting === u.idUsuario}
                          style={{ padding: "6px 10px", borderRadius: "var(--radius-sm)", border: "none", background: "var(--red-tint)", color: "var(--red)", display: "flex", alignItems: "center", fontSize: 12 }}>
                          {deleting === u.idUsuario ? "..." : <Trash2 size={13} />}
                        </button>
                      </div>
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

function SectionDivider({ children }: { children: React.ReactNode }) {
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

function FieldLabel({ children }: { children: React.ReactNode }) {
  return (
    <label style={{ fontSize: 11, fontWeight: 700, color: "var(--ink-3)", display: "block", marginBottom: 6, letterSpacing: "0.02em" }}>
      {children}
    </label>
  );
}
