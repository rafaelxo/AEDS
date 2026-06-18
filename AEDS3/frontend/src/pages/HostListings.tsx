import { useEffect, useState, useCallback } from "react";
import {
  Plus,
  Building2,
  Edit2,
  Trash2,
  MapPin,
  Upload,
  ChevronLeft,
} from "lucide-react";
import {
  imoveisService,
  comodidadeService,
  type Imovel,
  type ComodidadeCatalogo,
} from "../services/api";
import { useStore } from "../app/store";
import { geocodeAddressInput } from "../services/geocoding";

function fmt(v: number) {
  return v.toLocaleString("pt-BR", { style: "currency", currency: "BRL", maximumFractionDigits: 0 });
}

type View = "list" | "form";

interface FormState {
  titulo: string;
  descricao: string;
  cidade: string;
  estado: string;
  rua: string;
  numero: string;
  bairro: string;
  cep: string;
  valorDiaria: string;
  ativo: boolean;
  selectedComodidades: number[];
}

const MAX_PHOTOS = 5;

const EMPTY_FORM: FormState = {
  titulo: "",
  descricao: "",
  cidade: "",
  estado: "",
  rua: "",
  numero: "",
  bairro: "",
  cep: "",
  valorDiaria: "",
  ativo: true,
  selectedComodidades: [],
};

export default function HostListings() {
  const { user, openDetail } = useStore();
  const [view, setView] = useState<View>("list");
  const [listings, setListings] = useState<Imovel[]>([]);
  const [loading, setLoading] = useState(true);
  const [amenities, setAmenities] = useState<ComodidadeCatalogo[]>([]);
  const [editing, setEditing] = useState<Imovel | null>(null);
  const [form, setForm] = useState<FormState>(EMPTY_FORM);
  const [files, setFiles] = useState<File[]>([]);
  const [previewUrls, setPreviewUrls] = useState<string[]>([]);
  const [submitting, setSubmitting] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [deleting, setDeleting] = useState<number | null>(null);

  const fetchListings = useCallback(async () => {
    if (!user) return;
    setLoading(true);
    try {
      const data = await imoveisService.getByOwner(user.idUsuario);
      setListings(data);
    } finally {
      setLoading(false);
    }
  }, [user]);

  useEffect(() => {
    fetchListings();
    comodidadeService.getAll().then((a) => setAmenities(a.filter((x) => x.ativo)));
  }, [fetchListings]);

  useEffect(() => {
    const urls = files.map((f) => URL.createObjectURL(f));
    setPreviewUrls(urls);
    return () => urls.forEach((u) => URL.revokeObjectURL(u));
  }, [files]);

  const openNew = () => {
    setEditing(null);
    setForm(EMPTY_FORM);
    setFiles([]);
    setError(null);
    setView("form");
  };

  const openEdit = (p: Imovel) => {
    setEditing(p);
    setForm({
      titulo: p.titulo,
      descricao: p.descricao,
      cidade: p.cidade,
      estado: p.endereco.estado,
      rua: p.endereco.rua,
      numero: p.endereco.numero,
      bairro: p.endereco.bairro,
      cep: p.endereco.cep,
      valorDiaria: String(p.valorDiaria),
      ativo: p.ativo,
      selectedComodidades: p.comodidades.map((c) => c.idComodidade ?? 0).filter(Boolean),
    });
    setFiles([]);
    setError(null);
    setView("form");
  };

  const handleDelete = async (p: Imovel) => {
    if (!confirm(`Excluir "${p.titulo}"?`)) return;
    setDeleting(p.idImovel);
    try {
      await imoveisService.delete(p.idImovel);
      setListings((prev) => prev.filter((l) => l.idImovel !== p.idImovel));
    } catch (e) {
      alert(e instanceof Error ? e.message : "Erro ao excluir");
    } finally {
      setDeleting(null);
    }
  };

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    if (!user) return;
    if (!editing && files.length === 0) {
      setError("Adicione ao menos uma foto.");
      return;
    }
    setSubmitting(true);
    setError(null);
    try {
      const coords = await geocodeAddressInput(
        { rua: form.rua, numero: form.numero, bairro: form.bairro, cidade: form.cidade, estado: form.estado, cep: form.cep },
        form.cidade,
      );
      const base = {
        idUsuario: user.idUsuario,
        titulo: form.titulo,
        descricao: form.descricao,
        cidade: form.cidade,
        latitude: coords?.[0] ?? 0,
        longitude: coords?.[1] ?? 0,
        valorDiaria: Number(form.valorDiaria),
        dataCadastro: new Date().toISOString().slice(0, 10),
        ativo: form.ativo,
        endereco: {
          rua: form.rua,
          numero: form.numero,
          bairro: form.bairro,
          cidade: form.cidade,
          estado: form.estado,
          cep: form.cep,
        },
        comodidades: form.selectedComodidades.map((id) => {
          const a = amenities.find((x) => x.idComodidade === id);
          return { nome: a?.nome ?? String(id), idComodidade: id };
        }),
      };

      if (editing) {
        await imoveisService.updateWithFiles(editing.idImovel, base, files.length ? files : undefined);
      } else {
        await imoveisService.createWithFiles(base, files);
      }
      await fetchListings();
      setView("list");
    } catch (e) {
      setError(e instanceof Error ? e.message : "Erro ao salvar imóvel");
    } finally {
      setSubmitting(false);
    }
  };

  if (view === "form") {
    return (
      <div style={{ padding: "28px 36px", maxWidth: 720, margin: "0 auto" }}>
        <div style={{ display: "flex", alignItems: "center", gap: 12, marginBottom: 24 }}>
          <button
            onClick={() => setView("list")}
            style={{ background: "none", border: "none", color: "var(--ink-3)", display: "flex", alignItems: "center", gap: 6, fontSize: 13, fontWeight: 600 }}
          >
            <ChevronLeft size={16} /> Voltar
          </button>
          <h1 style={{ fontSize: 20, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.03em", margin: 0 }}>
            {editing ? "Editar imóvel" : "Novo imóvel"}
          </h1>
        </div>

        <form onSubmit={handleSubmit} style={{ display: "flex", flexDirection: "column", gap: 20 }}>
          <FormSection title="Informações básicas">
            <FormField label="Título" required>
              <input className="field-input" placeholder="Ex: Apartamento moderno no centro" value={form.titulo} onChange={(e) => setForm((f) => ({ ...f, titulo: e.target.value }))} required minLength={4} />
            </FormField>
            <FormField label="Descrição" required>
              <textarea className="field-input" rows={3} placeholder="Descreva seu imóvel..." value={form.descricao} onChange={(e) => setForm((f) => ({ ...f, descricao: e.target.value }))} required style={{ resize: "none" }} />
            </FormField>
            <FormField label="Valor da diária (R$)" required>
              <input className="field-input" type="number" min={1} placeholder="250" value={form.valorDiaria} onChange={(e) => setForm((f) => ({ ...f, valorDiaria: e.target.value }))} required />
            </FormField>
          </FormSection>

          <FormSection title="Endereço">
            <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 10 }}>
              <FormField label="Cidade" required>
                <input className="field-input" placeholder="São Paulo" value={form.cidade} onChange={(e) => setForm((f) => ({ ...f, cidade: e.target.value }))} required />
              </FormField>
              <FormField label="Estado" required>
                <input className="field-input" placeholder="SP" maxLength={2} value={form.estado} onChange={(e) => setForm((f) => ({ ...f, estado: e.target.value.toUpperCase() }))} required />
              </FormField>
              <FormField label="Rua" required>
                <input className="field-input" placeholder="Rua das Flores" value={form.rua} onChange={(e) => setForm((f) => ({ ...f, rua: e.target.value }))} required />
              </FormField>
              <FormField label="Número" required>
                <input className="field-input" placeholder="123" value={form.numero} onChange={(e) => setForm((f) => ({ ...f, numero: e.target.value }))} required />
              </FormField>
              <FormField label="Bairro" required>
                <input className="field-input" placeholder="Centro" value={form.bairro} onChange={(e) => setForm((f) => ({ ...f, bairro: e.target.value }))} required />
              </FormField>
              <FormField label="CEP" required>
                <input className="field-input" placeholder="01000-000" value={form.cep} onChange={(e) => setForm((f) => ({ ...f, cep: e.target.value }))} required />
              </FormField>
            </div>
          </FormSection>

          <FormSection title={editing ? `Fotos — ${files.length}/${MAX_PHOTOS} novas selecionadas` : `Fotos * — ${files.length}/${MAX_PHOTOS}`}>
            {editing && editing.fotos.length > 0 && (
              <div style={{ marginBottom: 12 }}>
                <p style={{ fontSize: 10, fontWeight: 700, letterSpacing: "0.08em", color: "var(--ink-4)", textTransform: "uppercase", margin: "0 0 8px" }}>
                  Fotos atuais{files.length > 0 ? " — serão substituídas" : ""}
                </p>
                <div style={{ display: "flex", gap: 8, flexWrap: "wrap" }}>
                  {editing.fotos.map((url, i) => (
                    <div key={i} style={{ width: 72, height: 72, borderRadius: "var(--radius-sm)", overflow: "hidden", opacity: files.length > 0 ? 0.35 : 1, transition: "opacity 200ms ease" }}>
                      <img src={url} alt="" style={{ width: "100%", height: "100%", objectFit: "cover" }} />
                    </div>
                  ))}
                </div>
              </div>
            )}

            <div style={{ display: "flex", gap: 10, flexWrap: "wrap" }}>
              {previewUrls.map((url, i) => (
                <div key={i} style={{ width: 100, height: 100, borderRadius: "var(--radius-md)", overflow: "hidden", position: "relative", flexShrink: 0 }}>
                  <img src={url} alt="" style={{ width: "100%", height: "100%", objectFit: "cover" }} />
                  <button
                    type="button"
                    onClick={() => setFiles((prev) => prev.filter((_, idx) => idx !== i))}
                    style={{ position: "absolute", top: 4, right: 4, width: 20, height: 20, borderRadius: "50%", background: "rgba(0,0,0,0.55)", border: "none", color: "#fff", display: "flex", alignItems: "center", justifyContent: "center", fontSize: 13, cursor: "pointer", lineHeight: 1 }}
                  >
                    ×
                  </button>
                  <div style={{ position: "absolute", bottom: 4, left: 6, fontSize: 9, fontWeight: 700, color: "rgba(255,255,255,0.7)" }}>
                    {i + 1}
                  </div>
                </div>
              ))}

              {files.length < MAX_PHOTOS && (
                <label
                  style={{ width: 100, height: 100, borderRadius: "var(--radius-md)", border: "2px dashed var(--border-strong)", display: "flex", flexDirection: "column", alignItems: "center", justifyContent: "center", cursor: "pointer", gap: 5, flexShrink: 0, transition: "border-color 140ms ease" }}
                  onMouseEnter={(e) => ((e.currentTarget as HTMLElement).style.borderColor = "var(--accent)")}
                  onMouseLeave={(e) => ((e.currentTarget as HTMLElement).style.borderColor = "var(--border-strong)")}
                >
                  <Upload size={18} style={{ color: "var(--accent)" }} />
                  <span style={{ fontSize: 10, fontWeight: 600, color: "var(--ink-4)" }}>Adicionar</span>
                  <input
                    type="file"
                    accept="image/*"
                    multiple
                    style={{ display: "none" }}
                    onChange={(e) => {
                      const picked = Array.from(e.target.files ?? []);
                      setFiles((prev) => [...prev, ...picked].slice(0, MAX_PHOTOS));
                      e.target.value = "";
                    }}
                  />
                </label>
              )}

              {Array.from({ length: Math.max(0, MAX_PHOTOS - files.length - (files.length < MAX_PHOTOS ? 1 : 0)) }).map((_, i) => (
                <div key={i} style={{ width: 100, height: 100, borderRadius: "var(--radius-md)", border: "1.5px dashed var(--border)", background: "var(--canvas)", flexShrink: 0, opacity: 0.45 }} />
              ))}
            </div>

            <p style={{ fontSize: 11, color: "var(--ink-4)", margin: "4px 0 0", fontWeight: 500 }}>
              Máximo de {MAX_PHOTOS} fotos · a primeira será a capa do imóvel
            </p>
          </FormSection>

          {amenities.length > 0 && (
            <FormSection title="Comodidades">
              <div style={{ display: "flex", flexWrap: "wrap", gap: 8 }}>
                {amenities.map((a) => {
                  const active = form.selectedComodidades.includes(a.idComodidade);
                  return (
                    <button
                      key={a.idComodidade}
                      type="button"
                      onClick={() =>
                        setForm((f) => ({
                          ...f,
                          selectedComodidades: active
                            ? f.selectedComodidades.filter((id) => id !== a.idComodidade)
                            : [...f.selectedComodidades, a.idComodidade],
                        }))
                      }
                      style={{
                        padding: "6px 14px",
                        borderRadius: "99px",
                        border: `1.5px solid ${active ? "var(--accent)" : "var(--border)"}`,
                        background: active ? "var(--accent-tint)" : "var(--surface)",
                        color: active ? "var(--accent)" : "var(--ink-3)",
                        fontSize: 12,
                        fontWeight: 600,
                        transition: "all 120ms ease",
                      }}
                    >
                      {a.nome}
                    </button>
                  );
                })}
              </div>
            </FormSection>
          )}

          <div style={{ display: "flex", alignItems: "center", gap: 12 }}>
            <label style={{ display: "flex", alignItems: "center", gap: 8, cursor: "pointer", fontSize: 14, fontWeight: 600, color: "var(--ink)" }}>
              <input
                type="checkbox"
                checked={form.ativo}
                onChange={(e) => setForm((f) => ({ ...f, ativo: e.target.checked }))}
                style={{ width: 16, height: 16, accentColor: "var(--accent)" }}
              />
              Imóvel ativo (visível no mapa)
            </label>
          </div>

          {error && (
            <div style={{ padding: "10px 14px", borderRadius: "var(--radius-md)", background: "var(--red-tint)", color: "var(--red)", fontSize: 13 }}>
              {error}
            </div>
          )}

          <div style={{ display: "flex", gap: 10, justifyContent: "flex-end" }}>
            <button type="button" onClick={() => setView("list")} className="btn btn-secondary">
              Cancelar
            </button>
            <button type="submit" disabled={submitting} className="btn btn-primary">
              {submitting ? "Salvando..." : editing ? "Salvar alterações" : "Publicar imóvel"}
            </button>
          </div>
        </form>
      </div>
    );
  }

  return (
    <div style={{ padding: "28px 36px" }}>
      <div style={{ display: "flex", alignItems: "center", justifyContent: "space-between", marginBottom: 24 }}>
        <div>
          <h1 style={{ fontSize: 22, fontWeight: 800, color: "var(--ink)", letterSpacing: "-0.04em", margin: "0 0 4px" }}>
            Meus Imóveis
          </h1>
          <p style={{ fontSize: 13, color: "var(--ink-3)", margin: 0 }}>
            {listings.length} imóvel(is) cadastrado(s)
          </p>
        </div>
        <button onClick={openNew} className="btn btn-primary">
          <Plus size={15} /> Novo imóvel
        </button>
      </div>

      {loading ? (
        <div style={{ display: "grid", gridTemplateColumns: "repeat(auto-fill, minmax(280px, 1fr))", gap: 16 }}>
          {[1, 2, 3].map((i) => (
            <div key={i} style={{ height: 280, borderRadius: "var(--radius-lg)", background: "var(--canvas)" }} />
          ))}
        </div>
      ) : listings.length === 0 ? (
        <div style={{ padding: "64px 0", textAlign: "center" }}>
          <Building2 size={48} style={{ color: "var(--ink-5)", margin: "0 auto 16px" }} />
          <h2 style={{ fontSize: 18, fontWeight: 700, color: "var(--ink)", margin: "0 0 8px" }}>
            Nenhum imóvel cadastrado
          </h2>
          <p style={{ fontSize: 14, color: "var(--ink-3)", margin: "0 0 20px" }}>
            Publique seu primeiro imóvel e comece a receber hóspedes.
          </p>
          <button onClick={openNew} className="btn btn-primary">
            <Plus size={15} /> Cadastrar imóvel
          </button>
        </div>
      ) : (
        <div style={{ display: "grid", gridTemplateColumns: "repeat(auto-fill, minmax(280px, 1fr))", gap: 16 }}>
          {listings.map((p) => (
            <ListingCard
              key={p.idImovel}
              property={p}
              onEdit={() => openEdit(p)}
              onDelete={() => handleDelete(p)}
              onView={() => openDetail(p.idImovel)}
              deleting={deleting === p.idImovel}
            />
          ))}
        </div>
      )}
    </div>
  );
}

function ListingCard({
  property: p,
  onEdit,
  onDelete,
  onView,
  deleting,
}: {
  property: Imovel;
  onEdit: () => void;
  onDelete: () => void;
  onView: () => void;
  deleting: boolean;
}) {
  return (
    <div className="card card-hover" style={{ overflow: "hidden", display: "flex", flexDirection: "column" }}>
      <div style={{ height: 160, background: "var(--canvas)", position: "relative", flexShrink: 0 }}>
        {p.fotos?.[0] ? (
          <img src={p.fotos[0]} alt={p.titulo} style={{ width: "100%", height: "100%", objectFit: "cover" }} />
        ) : (
          <div style={{ width: "100%", height: "100%", display: "flex", alignItems: "center", justifyContent: "center" }}>
            <Building2 size={32} style={{ color: "var(--ink-5)" }} />
          </div>
        )}
        <span
          className={`badge ${p.ativo ? "badge-green" : "badge-ink"}`}
          style={{ position: "absolute", top: 10, left: 10 }}
        >
          {p.ativo ? "Ativo" : "Inativo"}
        </span>
      </div>

      <div style={{ padding: "14px 16px", flex: 1 }}>
        <div style={{ fontSize: 14, fontWeight: 700, color: "var(--ink)", marginBottom: 4, overflow: "hidden", textOverflow: "ellipsis", whiteSpace: "nowrap" }}>
          {p.titulo}
        </div>
        <div style={{ fontSize: 12, color: "var(--ink-3)", marginBottom: 8, display: "flex", alignItems: "center", gap: 4 }}>
          <MapPin size={11} /> {p.cidade} · {p.endereco.estado}
        </div>
        <div style={{ fontSize: 15, fontWeight: 800, color: "var(--accent)", letterSpacing: "-0.02em" }}>
          {fmt(p.valorDiaria)}
          <span style={{ fontSize: 11, fontWeight: 400, color: "var(--ink-3)" }}>/noite</span>
        </div>
      </div>

      <div style={{ padding: "10px 16px 14px", display: "flex", gap: 8, borderTop: "1px solid var(--border)" }}>
        <button onClick={onView} className="btn btn-secondary btn-sm" style={{ flex: 1 }}>
          Detalhes
        </button>
        <button onClick={onEdit} className="btn btn-ghost btn-sm" style={{ display: "flex", alignItems: "center", gap: 4 }}>
          <Edit2 size={13} />
        </button>
        <button
          onClick={onDelete}
          disabled={deleting}
          style={{
            padding: "6px 10px",
            borderRadius: "var(--radius-sm)",
            border: "none",
            background: "var(--red-tint)",
            color: "var(--red)",
            display: "flex",
            alignItems: "center",
            fontSize: 12,
          }}
        >
          {deleting ? "..." : <Trash2 size={13} />}
        </button>
      </div>
    </div>
  );
}

function FormSection({ title, children }: { title: string; children: React.ReactNode }) {
  return (
    <div className="card" style={{ padding: "20px 24px" }}>
      <h3 style={{ fontSize: 13, fontWeight: 700, color: "var(--ink-3)", textTransform: "uppercase", letterSpacing: "0.06em", margin: "0 0 16px" }}>
        {title}
      </h3>
      <div style={{ display: "flex", flexDirection: "column", gap: 12 }}>{children}</div>
    </div>
  );
}

function FormField({ label, required, children }: { label: string; required?: boolean; children: React.ReactNode }) {
  return (
    <div>
      <label style={{ fontSize: 12, fontWeight: 600, color: "var(--ink-3)", display: "block", marginBottom: 6 }}>
        {label} {required && <span style={{ color: "var(--red)" }}>*</span>}
      </label>
      {children}
    </div>
  );
}
