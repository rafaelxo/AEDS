import { useState } from "react";
import { useNavigate } from "react-router-dom";
import { Eye, EyeOff, ArrowRight, User, Mail, Lock, Phone } from "lucide-react";
import { authService } from "../../services/api";
import { useStore } from "../../app/store";

type Tab = "login" | "register";
type Role = "hospede" | "anfitriao";

export default function AuthPanel() {
  const [tab, setTab] = useState<Tab>("login");
  const { setUser } = useStore();
  const navigate = useNavigate();

  const handleSuccess = (me: { tipo: string }) => {
    if (me.tipo === "ADMIN") navigate("/admin", { replace: true });
    else if (me.tipo === "ANFITRIAO") navigate("/host", { replace: true });
    else navigate("/dashboard", { replace: true });
  };

  return (
    <div
      style={{
        width: "100%",
        maxWidth: 420,
        margin: "0 auto",
      }}
    >
      <div
        style={{
          display: "flex",
          background: "var(--surface-dim)",
          borderRadius: "var(--radius-lg)",
          padding: 4,
          marginBottom: 28,
        }}
      >
        {(["login", "register"] as Tab[]).map((t) => (
          <button
            key={t}
            onClick={() => setTab(t)}
            style={{
              flex: 1,
              padding: "9px 16px",
              borderRadius: "var(--radius-md)",
              border: "none",
              background: tab === t ? "var(--surface)" : "transparent",
              color: tab === t ? "var(--ink)" : "var(--ink-3)",
              fontWeight: tab === t ? 600 : 500,
              fontSize: 13,
              boxShadow: tab === t ? "var(--shadow-xs)" : "none",
              transition: "all 160ms ease",
            }}
          >
            {t === "login" ? "Entrar" : "Criar conta"}
          </button>
        ))}
      </div>

      {tab === "login" ? (
        <LoginForm onSuccess={handleSuccess} setUser={setUser} />
      ) : (
        <RegisterForm onSuccess={handleSuccess} setUser={setUser} />
      )}
    </div>
  );
}

function LoginForm({
  onSuccess,
  setUser,
}: {
  onSuccess: (me: { tipo: string }) => void;
  setUser: (u: any) => void;
}) {
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [showPw, setShowPw] = useState(false);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setLoading(true);
    setError(null);
    try {
      const session = await authService.login(email, password);
      setUser(session.usuario);
      onSuccess(session.usuario);
    } catch (err) {
      const raw = err instanceof Error ? err.message : "Erro ao entrar";
      setError(friendlyError(raw, "login"));
    } finally {
      setLoading(false);
    }
  };

  return (
    <form onSubmit={handleSubmit} style={{ display: "flex", flexDirection: "column", gap: 14 }}>
      <FieldInput
        icon={<Mail size={15} />}
        type="email"
        placeholder="seu@email.com"
        value={email}
        onChange={setEmail}
        required
        autoComplete="email"
      />
      <div style={{ position: "relative" }}>
        <FieldInput
          icon={<Lock size={15} />}
          type={showPw ? "text" : "password"}
          placeholder="Senha"
          value={password}
          onChange={setPassword}
          required
          autoComplete="current-password"
        />
        <button
          type="button"
          onClick={() => setShowPw((v) => !v)}
          style={{
            position: "absolute",
            right: 14,
            top: "50%",
            transform: "translateY(-50%)",
            background: "none",
            border: "none",
            color: "var(--ink-4)",
            padding: 0,
            display: "flex",
          }}
        >
          {showPw ? <EyeOff size={15} /> : <Eye size={15} />}
        </button>
      </div>

      {error && <ErrorNote message={error} />}

      <button
        type="submit"
        disabled={loading}
        className="btn btn-primary btn-lg"
        style={{ marginTop: 4, width: "100%", justifyContent: "space-between" }}
      >
        {loading ? "Entrando..." : "Entrar na plataforma"}
        {!loading && <ArrowRight size={16} />}
      </button>
    </form>
  );
}

function RegisterForm({
  onSuccess,
  setUser,
}: {
  onSuccess: (me: { tipo: string }) => void;
  setUser: (u: any) => void;
}) {
  const [role, setRole] = useState<Role>("hospede");
  const [nome, setNome] = useState("");
  const [email, setEmail] = useState("");
  const [telefone, setTelefone] = useState("");
  const [password, setPassword] = useState("");
  const [showPw, setShowPw] = useState(false);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  /* host-only property fields */
  const [propTitulo, setPropTitulo] = useState("");
  const [propDescricao, setPropDescricao] = useState("");
  const [propCidade, setPropCidade] = useState("");
  const [propEstado, setPropEstado] = useState("");
  const [propRua, setPropRua] = useState("");
  const [propNumero, setPropNumero] = useState("");
  const [propBairro, setPropBairro] = useState("");
  const [propCep, setPropCep] = useState("");
  const [propValor, setPropValor] = useState("");
  const [propFiles, setPropFiles] = useState<File[]>([]);

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setLoading(true);
    setError(null);

    try {
      if (role === "hospede") {
        const session = await authService.register({
          nome,
          email,
          telefone: telefone || undefined,
          senha: password,
          comoAnfitriao: false,
        });
        setUser(session.usuario);
        onSuccess(session.usuario);
        return;
      }

      /* host — need to convert first photo to base64 */
      if (propFiles.length === 0) {
        setError("Adicione ao menos uma foto do imóvel.");
        setLoading(false);
        return;
      }

      const toBase64 = (file: File): Promise<string> =>
        new Promise((res, rej) => {
          const reader = new FileReader();
          reader.onload = () => res(reader.result as string);
          reader.onerror = rej;
          reader.readAsDataURL(file);
        });

      const fotoBase64 = await toBase64(propFiles[0]);

      const session = await authService.register({
        nome,
        email,
        telefone: telefone || undefined,
        senha: password,
        comoAnfitriao: true,
        imovelInicial: {
          titulo: propTitulo,
          descricao: propDescricao,
          endereco: {
            rua: propRua,
            numero: propNumero,
            bairro: propBairro,
            cidade: propCidade,
            estado: propEstado,
            cep: propCep,
          },
          comodidades: [],
          cidade: propCidade,
          valorDiaria: Number(propValor),
          dataCadastro: new Date().toISOString().slice(0, 10),
          fotos: [fotoBase64],
          ativo: true,
        },
      });
      setUser(session.usuario);
      onSuccess(session.usuario);
    } catch (err) {
      const raw = err instanceof Error ? err.message : "Erro ao criar conta";
      setError(friendlyError(raw, "register"));
    } finally {
      setLoading(false);
    }
  };

  return (
    <form onSubmit={handleSubmit} style={{ display: "flex", flexDirection: "column", gap: 14 }}>
      <div
        style={{
          display: "grid",
          gridTemplateColumns: "1fr 1fr",
          gap: 8,
          marginBottom: 4,
        }}
      >
        {(["hospede", "anfitriao"] as Role[]).map((r) => (
          <button
            key={r}
            type="button"
            onClick={() => setRole(r)}
            style={{
              padding: "10px",
              borderRadius: "var(--radius-md)",
              border: `1.5px solid ${role === r ? "var(--accent)" : "var(--border)"}`,
              background: role === r ? "var(--accent-tint)" : "var(--surface)",
              color: role === r ? "var(--accent)" : "var(--ink-3)",
              fontWeight: 600,
              fontSize: 12,
              textAlign: "center",
              transition: "all 140ms ease",
            }}
          >
            {r === "hospede" ? "🏡 Hóspede" : "🏠 Anfitrião"}
          </button>
        ))}
      </div>

      <FieldInput
        icon={<User size={15} />}
        type="text"
        placeholder="Nome completo"
        value={nome}
        onChange={setNome}
        required
      />
      <FieldInput
        icon={<Mail size={15} />}
        type="email"
        placeholder="seu@email.com"
        value={email}
        onChange={setEmail}
        required
        autoComplete="email"
      />
      <FieldInput
        icon={<Phone size={15} />}
        type="tel"
        placeholder="Telefone (opcional)"
        value={telefone}
        onChange={setTelefone}
      />
      <div style={{ position: "relative" }}>
        <FieldInput
          icon={<Lock size={15} />}
          type={showPw ? "text" : "password"}
          placeholder="Crie uma senha"
          value={password}
          onChange={setPassword}
          required
          autoComplete="new-password"
        />
        <button
          type="button"
          onClick={() => setShowPw((v) => !v)}
          style={{
            position: "absolute",
            right: 14,
            top: "50%",
            transform: "translateY(-50%)",
            background: "none",
            border: "none",
            color: "var(--ink-4)",
            padding: 0,
            display: "flex",
          }}
        >
          {showPw ? <EyeOff size={15} /> : <Eye size={15} />}
        </button>
      </div>

      {role === "anfitriao" && (
        <div
          style={{
            display: "flex",
            flexDirection: "column",
            gap: 10,
            paddingTop: 4,
            borderTop: "1px solid var(--border)",
          }}
        >
          <p style={{ fontSize: 11, color: "var(--ink-3)", fontWeight: 600, letterSpacing: "0.06em", textTransform: "uppercase" }}>
            Seu primeiro imóvel
          </p>
          <input className="field-input" placeholder="Título do imóvel" value={propTitulo} onChange={(e) => setPropTitulo(e.target.value)} required />
          <textarea className="field-input" rows={2} placeholder="Descrição" value={propDescricao} onChange={(e) => setPropDescricao(e.target.value)} required style={{ resize: "none" }} />
          <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 8 }}>
            <input className="field-input" placeholder="Cidade" value={propCidade} onChange={(e) => setPropCidade(e.target.value)} required />
            <input className="field-input" placeholder="Estado (UF)" value={propEstado} onChange={(e) => setPropEstado(e.target.value.toUpperCase())} required maxLength={2} />
          </div>
          <div style={{ display: "grid", gridTemplateColumns: "2fr 1fr", gap: 8 }}>
            <input className="field-input" placeholder="Rua" value={propRua} onChange={(e) => setPropRua(e.target.value)} required />
            <input className="field-input" placeholder="Nº" value={propNumero} onChange={(e) => setPropNumero(e.target.value)} required />
          </div>
          <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 8 }}>
            <input className="field-input" placeholder="Bairro" value={propBairro} onChange={(e) => setPropBairro(e.target.value)} required />
            <input className="field-input" placeholder="CEP" value={propCep} onChange={(e) => setPropCep(e.target.value)} required />
          </div>
          <input className="field-input" type="number" min="1" placeholder="Valor da diária (R$)" value={propValor} onChange={(e) => setPropValor(e.target.value)} required />
          <label
            style={{
              display: "flex",
              alignItems: "center",
              gap: 10,
              padding: "10px 14px",
              border: "1.5px dashed var(--border-strong)",
              borderRadius: "var(--radius-md)",
              cursor: "pointer",
              fontSize: 13,
              color: propFiles.length ? "var(--ink)" : "var(--ink-4)",
            }}
          >
            📷{" "}
            {propFiles.length > 0
              ? `${propFiles.length} foto(s) selecionada(s)`
              : "Adicionar foto do imóvel"}
            <input
              type="file"
              accept="image/*"
              multiple
              style={{ display: "none" }}
              onChange={(e) => setPropFiles(Array.from(e.target.files ?? []))}
            />
          </label>
        </div>
      )}

      {error && <ErrorNote message={error} />}

      <button
        type="submit"
        disabled={loading}
        className="btn btn-primary btn-lg"
        style={{ marginTop: 4, width: "100%", justifyContent: "space-between" }}
      >
        {loading ? "Criando conta..." : "Criar conta grátis"}
        {!loading && <ArrowRight size={16} />}
      </button>
    </form>
  );
}

function FieldInput({
  icon,
  ...props
}: {
  icon?: React.ReactNode;
  type: string;
  placeholder: string;
  value: string;
  onChange: (v: string) => void;
  required?: boolean;
  autoComplete?: string;
}) {
  const { onChange: _onChange, ...rest } = props;
  return (
    <div style={{ position: "relative", display: "flex", alignItems: "center" }}>
      {icon && (
        <span
          style={{
            position: "absolute",
            left: 13,
            color: "var(--ink-4)",
            display: "flex",
            pointerEvents: "none",
          }}
        >
          {icon}
        </span>
      )}
      <input
        {...rest}
        value={props.value}
        onChange={(e) => props.onChange(e.target.value)}
        className="field-input"
        style={{ paddingLeft: icon ? 38 : 14 }}
      />
    </div>
  );
}

function friendlyError(raw: string, ctx: "login" | "register"): string {
  const m = raw.toLowerCase();
  if (m === "network_error" || m.includes("network_error") || m.includes("failed to fetch"))
    return "Não foi possível conectar ao servidor. Verifique se o backend está rodando.";
  if (m.includes("401") || m.includes("invalid credential") || m.includes("unauthorized") || m.includes("senha") || m.includes("credenci"))
    return ctx === "login"
      ? "E-mail ou senha incorretos. Verifique os dados e tente novamente."
      : "Credenciais inválidas.";
  if (m.includes("404"))
    return ctx === "login"
      ? "Nenhuma conta encontrada com este e-mail."
      : "Recurso não encontrado.";
  if (m.includes("409") || m.includes("already") || m.includes("exist") || m.includes("já cadastr") || m.includes("duplicate"))
    return "Este e-mail já está cadastrado. Tente fazer login.";
  if (m.includes("400") || m.includes("invalid") || m.includes("inválid") || m.includes("required") || m.includes("obrigat"))
    return "Dados inválidos. Verifique os campos e tente novamente.";
  if (m.includes("500") || m.includes("internal server"))
    return "Erro interno do servidor. Tente novamente em instantes.";
  if (m.includes("503") || m.includes("unavailable"))
    return "Serviço temporariamente indisponível. Tente novamente em breve.";
  return raw.startsWith("Erro ") || raw.startsWith("Não ") || raw.startsWith("Este ")
    ? raw
    : "Ocorreu um erro inesperado. Tente novamente.";
}

function ErrorNote({ message }: { message: string }) {
  return (
    <div
      style={{
        padding: "10px 14px",
        borderRadius: "var(--radius-md)",
        background: "var(--red-tint)",
        color: "var(--red)",
        fontSize: 13,
        fontWeight: 500,
      }}
    >
      {message}
    </div>
  );
}
