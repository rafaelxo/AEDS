const BASE_URL = "http://localhost:8080";
const TOKEN_KEY = "hostly_token";

export interface Imovel {
  idImovel: number;
  idUsuario: number;
  titulo: string;
  descricao: string;
  endereco: {
    rua: string;
    numero: string;
    bairro: string;
    cidade: string;
    estado: string;
    cep: string;
  };
  comodidades: {
    idComodidade?: number;
    nome: string;
    descricao?: string;
  }[];
  cidade: string;
  latitude?: number;
  longitude?: number;
  valorDiaria: number;
  dataCadastro: string;
  fotos: string[];
  ativo: boolean;
}

export interface ComodidadeCatalogo {
  idComodidade: number;
  nome: string;
  descricao?: string;
  icone?: string;
  ativo: boolean;
}

export type CreateComodidadeInput = {
  nome: string;
  descricao?: string;
  icone?: string;
  ativo: boolean;
};

export type UpdateComodidadeInput = Partial<CreateComodidadeInput>;

export type UsuarioTipo = "ADMIN" | "ANFITRIAO" | "HOSPEDE";

export interface Usuario {
  idUsuario: number;
  nome: string;
  email: string;
  telefone?: string;
  tipo: UsuarioTipo;
  ativo: boolean;
}

export interface Session {
  token: string;
  usuario: Usuario;
}

export interface Reserva {
  idReserva: number;
  idImovel: number;
  idHospede: number;
  dataInicio: string;
  dataFim: string;
  valorTotal: number;
  status: "PENDENTE" | "CONFIRMADA" | "CANCELADA";
  formaPagamento:
    | ""
    | "PIX"
    | "CARTAO_CREDITO"
    | "CARTAO_DEBITO"
    | "BOLETO"
    | "DINHEIRO";
  statusPagamento: "NAO_INICIADO" | "PENDENTE" | "APROVADO" | "FALHOU";
  confirmadaEm?: string;
}

export interface DashboardStats {
  totalImoveis: number;
  totalAnfitrioes: number;
  totalReservas: number;
  receitaTotal: number;
}

export interface ImovelComodidade {
  idImovel: number;
  idComodidade: number;
  dataCadastro: string;
  ativo: boolean;
}

export type CreateUsuarioInput = {
  nome: string;
  email: string;
  telefone?: string;
  senha?: string;
  tipo: UsuarioTipo;
  ativo: boolean;
};

export type UpdateUsuarioInput = Partial<CreateUsuarioInput>;

export type CreateReservaInput = {
  idImovel: number;
  idHospede: number;
  dataInicio: string;
  dataFim: string;
  formaPagamento?: Reserva["formaPagamento"];
};
export type UpdateReservaInput = Partial<CreateReservaInput> & {
  status?: Reserva["status"];
};

async function request<T>(path: string, options?: RequestInit): Promise<T> {
  const token = localStorage.getItem(TOKEN_KEY);
  const isFormData = options?.body instanceof FormData;

  let res: Response;
  try {
    res = await fetch(`${BASE_URL}${path}`, {
      headers: {
        ...(isFormData ? {} : { "Content-Type": "application/json" }),
        ...(token ? { Authorization: `Bearer ${token}` } : {}),
        ...(options?.headers ?? {}),
      },
      ...options,
    });
  } catch {
    throw new Error("NETWORK_ERROR");
  }

  if (!res.ok) {
    const errorText = await res.text();
    let message = res.statusText;

    if (errorText) {
      try {
        const parsed = JSON.parse(errorText) as { error?: string };
        if (parsed.error) {
          message = parsed.error;
        }
      } catch {
        message = errorText;
      }
    }

    throw new Error(`${res.status}:${message}`);
  }

  if (res.status === 204) {
    return undefined as T;
  }

  const text = await res.text();
  if (!text) {
    return undefined as T;
  }

  return JSON.parse(text) as T;
}

export function saveSession(session: Session) {
  localStorage.setItem(TOKEN_KEY, session.token);
}

export function clearSession() {
  localStorage.removeItem(TOKEN_KEY);
}

export function hasSessionToken() {
  return Boolean(localStorage.getItem(TOKEN_KEY));
}

export const imoveisService = {
  async getAll(params?: {
    idUsuario?: number;
    cidade?: string;
    busca?: string;
    ativo?: boolean;
    ordenarPor?: "valorDiaria" | "cidade" | "dataCadastro" | "titulo";
    ordem?: "asc" | "desc";
    valorDiaria?: number;
    valorDiariaMin?: number;
    valorDiariaMax?: number;
    comodidades?: number[];
    algoritmo?: "bm" | "kmp";
  }): Promise<Imovel[]> {
    const query = new URLSearchParams();
    if (typeof params?.idUsuario === "number") {
      query.set("idUsuario", String(params.idUsuario));
    }
    if (params?.cidade?.trim()) {
      query.set("cidade", params.cidade.trim());
    }
    if (params?.busca?.trim()) {
      query.set("busca", params.busca.trim());
    }
    if (typeof params?.ativo === "boolean") {
      query.set("ativo", String(params.ativo));
    }
    if (params?.ordenarPor) {
      query.set("ordenarPor", params.ordenarPor);
    }
    if (params?.ordem) {
      query.set("ordem", params.ordem);
    }
    if (typeof params?.valorDiaria === "number") {
      query.set("valorDiaria", String(params.valorDiaria));
    }
    if (typeof params?.valorDiariaMin === "number") {
      query.set("valorDiariaMin", String(params.valorDiariaMin));
    }
    if (typeof params?.valorDiariaMax === "number") {
      query.set("valorDiariaMax", String(params.valorDiariaMax));
    }
    if (params?.comodidades?.length) {
      query.set("comodidades", params.comodidades.join(","));
    }
    if (params?.algoritmo) {
      query.set("algoritmo", params.algoritmo);
    }

    const qs = query.toString();
    return request<Imovel[]>(qs ? `/imoveis?${qs}` : "/imoveis");
  },
  async getByOwner(idUsuario: number): Promise<Imovel[]> {
    return request<Imovel[]>(`/imoveis/usuario/${idUsuario}`);
  },
  async getById(id: number): Promise<Imovel> {
    return request<Imovel>(`/imoveis/${id}`);
  },
  async create(data: Omit<Imovel, "idImovel">): Promise<Imovel> {
    return request<Imovel>("/imoveis", {
      method: "POST",
      body: JSON.stringify(data),
    });
  },
  async createWithFiles(
    data: Omit<Imovel, "idImovel" | "fotos">,
    files: File[],
  ): Promise<Imovel> {
    const formData = new FormData();
    formData.append("idUsuario", String(data.idUsuario));
    formData.append("titulo", data.titulo);
    formData.append("descricao", data.descricao);
    formData.append("cidade", data.cidade);
    formData.append("latitude", String(data.latitude ?? 0));
    formData.append("longitude", String(data.longitude ?? 0));
    formData.append("valorDiaria", String(data.valorDiaria));
    formData.append("dataCadastro", data.dataCadastro);
    formData.append("ativo", String(data.ativo));

    formData.append("endereco.rua", data.endereco.rua);
    formData.append("endereco.numero", data.endereco.numero);
    formData.append("endereco.bairro", data.endereco.bairro);
    formData.append("endereco.cidade", data.endereco.cidade);
    formData.append("endereco.estado", data.endereco.estado);
    formData.append("endereco.cep", data.endereco.cep);

    formData.append("comodidades", JSON.stringify(data.comodidades));

    files.forEach((file) => {
      formData.append("fotos", file);
    });

    return request<Imovel>("/imoveis", {
      method: "POST",
      body: formData,
    });
  },
  async updateWithFiles(
    id: number,
    data: Omit<Imovel, "idImovel" | "fotos">,
    files?: File[],
  ): Promise<Imovel> {
    const formData = new FormData();
    formData.append("idUsuario", String(data.idUsuario));
    formData.append("titulo", data.titulo);
    formData.append("descricao", data.descricao);
    formData.append("cidade", data.cidade);
    formData.append("latitude", String(data.latitude ?? 0));
    formData.append("longitude", String(data.longitude ?? 0));
    formData.append("valorDiaria", String(data.valorDiaria));
    formData.append("dataCadastro", data.dataCadastro);
    formData.append("ativo", String(data.ativo));

    formData.append("endereco.rua", data.endereco.rua);
    formData.append("endereco.numero", data.endereco.numero);
    formData.append("endereco.bairro", data.endereco.bairro);
    formData.append("endereco.cidade", data.endereco.cidade);
    formData.append("endereco.estado", data.endereco.estado);
    formData.append("endereco.cep", data.endereco.cep);

    formData.append("comodidades", JSON.stringify(data.comodidades));

    (files ?? []).forEach((file) => {
      formData.append("fotos", file);
    });

    return request<Imovel>(`/imoveis/${id}`, {
      method: "PUT",
      body: formData,
    });
  },
  async update(id: number, data: Partial<Imovel>): Promise<Imovel> {
    return request<Imovel>(`/imoveis/${id}`, {
      method: "PUT",
      body: JSON.stringify(data),
    });
  },
  async delete(id: number): Promise<void> {
    return request<void>(`/imoveis/${id}`, { method: "DELETE" });
  },
};


export const usuarioService = {
  async getAll(params?: { busca?: string; algoritmo?: "bm" | "kmp" }): Promise<Usuario[]> {
    const query = new URLSearchParams();
    if (params?.busca?.trim()) {
      query.set("busca", params.busca.trim());
    }
    if (params?.algoritmo) {
      query.set("algoritmo", params.algoritmo);
    }
    const qs = query.toString();
    return request<Usuario[]>(qs ? `/usuarios?${qs}` : "/usuarios");
  },
  async getById(id: number): Promise<Usuario> {
    return request<Usuario>(`/usuarios/${id}`);
  },
  async create(data: CreateUsuarioInput): Promise<Usuario> {
    return request<Usuario>("/usuarios", {
      method: "POST",
      body: JSON.stringify(data),
    });
  },
  async update(id: number, data: UpdateUsuarioInput): Promise<Usuario> {
    return request<Usuario>(`/usuarios/${id}`, {
      method: "PUT",
      body: JSON.stringify(data),
    });
  },
  async delete(id: number): Promise<void> {
    return request<void>(`/usuarios/${id}`, { method: "DELETE" });
  },
};

export const reservaService = {
  async getAll(params?: {
    idImovel?: number;
    idUsuario?: number;
    papel?: "hospede" | "anfitriao";
    busca?: string;
    status?: Reserva["status"];
    periodoDe?: string;
    periodoAte?: string;
    ordenarPor?: "dataInicio" | "dataFim" | "valorTotal";
    ordem?: "asc" | "desc";
    algoritmo?: "bm" | "kmp";
  }): Promise<Reserva[]> {
    const query = new URLSearchParams();
    if (typeof params?.idImovel === "number") {
      query.set("idImovel", String(params.idImovel));
    }
    if (typeof params?.idUsuario === "number") {
      query.set("idUsuario", String(params.idUsuario));
    }
    if (params?.papel) {
      query.set("papel", params.papel);
    }
    if (params?.busca?.trim()) {
      query.set("busca", params.busca.trim());
    }
    if (params?.status) {
      query.set("status", params.status);
    }
    if (params?.periodoDe) {
      query.set("periodoDe", params.periodoDe);
    }
    if (params?.periodoAte) {
      query.set("periodoAte", params.periodoAte);
    }
    if (params?.ordenarPor) {
      query.set("ordenarPor", params.ordenarPor);
    }
    if (params?.ordem) {
      query.set("ordem", params.ordem);
    }
    if (params?.algoritmo) {
      query.set("algoritmo", params.algoritmo);
    }

    const qs = query.toString();
    return request<Reserva[]>(qs ? `/reservas?${qs}` : "/reservas");
  },
  async getByImovel(idImovel: number): Promise<Reserva[]> {
    return this.getAll({ idImovel });
  },
  async getByHospede(idHospede: number): Promise<Reserva[]> {
    return request<Reserva[]>(`/reservas/hospede/${idHospede}`);
  },
  async getByAnfitriao(idAnfitriao: number): Promise<Reserva[]> {
    return request<Reserva[]>(`/reservas/anfitriao/${idAnfitriao}`);
  },
  async create(data: CreateReservaInput): Promise<Reserva> {
    return request<Reserva>("/reservas", {
      method: "POST",
      body: JSON.stringify(data),
    });
  },
  async update(id: number, data: UpdateReservaInput): Promise<Reserva> {
    return request<Reserva>(`/reservas/${id}`, {
      method: "PUT",
      body: JSON.stringify(data),
    });
  },
  async confirm(id: number, formaPagamento: Reserva["formaPagamento"]) {
    return request<Reserva>(`/reservas/${id}/confirmar`, {
      method: "PUT",
      body: JSON.stringify({ formaPagamento }),
    });
  },
  async delete(id: number): Promise<void> {
    return request<void>(`/reservas/${id}`, { method: "DELETE" });
  },
};

export const dashboardService = {
  async getStats(): Promise<DashboardStats> {
    return request<DashboardStats>("/dashboard/stats");
  },
};

export const comodidadeService = {
  async getAll(): Promise<ComodidadeCatalogo[]> {
    return request<ComodidadeCatalogo[]>("/comodidades");
  },
  async getById(id: number): Promise<ComodidadeCatalogo> {
    return request<ComodidadeCatalogo>(`/comodidades/${id}`);
  },
  async create(data: CreateComodidadeInput): Promise<ComodidadeCatalogo> {
    return request<ComodidadeCatalogo>("/comodidades", {
      method: "POST",
      body: JSON.stringify(data),
    });
  },
  async update(
    id: number,
    data: UpdateComodidadeInput,
  ): Promise<ComodidadeCatalogo> {
    return request<ComodidadeCatalogo>(`/comodidades/${id}`, {
      method: "PUT",
      body: JSON.stringify(data),
    });
  },
  async delete(id: number): Promise<void> {
    return request<void>(`/comodidades/${id}`, { method: "DELETE" });
  },
  async getImoveis(idComodidade: number): Promise<Imovel[]> {
    return request<Imovel[]>(
      `/imoveis-comodidades/comodidade/${idComodidade}/imoveis`,
    );
  },
  async linkImovel(
    idImovel: number,
    idComodidade: number,
  ): Promise<ImovelComodidade> {
    return request<ImovelComodidade>("/imoveis-comodidades", {
      method: "POST",
      body: JSON.stringify({
        idImovel,
        idComodidade,
        dataCadastro: new Date().toISOString().slice(0, 10),
        ativo: true,
      }),
    });
  },
  async unlinkImovel(idImovel: number, idComodidade: number): Promise<void> {
    return request<void>(
      `/imoveis-comodidades/imovel/${idImovel}/comodidade/${idComodidade}`,
      { method: "DELETE" },
    );
  },
};

export type AlgoritmoCompressao = "huffman" | "lzw";

export interface BackupResult {
  arquivo: string;
  algoritmo: AlgoritmoCompressao;
  arquivos: string[];
  tamanhoTotal: number;
  tamanhoBackup: number;
  taxa: number;
}

export interface BackupInfo {
  arquivo: string;
  algoritmo: string;
  tamanho: number;
  criadoEm: string;
}

export interface RestoreResult {
  arquivo: string;
  algoritmo: string;
  arquivos: string[];
}

export const backupService = {
  async create(algoritmo: AlgoritmoCompressao): Promise<BackupResult> {
    return request<BackupResult>("/backup", {
      method: "POST",
      body: JSON.stringify({ algoritmo }),
    });
  },
  async list(): Promise<BackupInfo[]> {
    return request<BackupInfo[]>("/backups");
  },
  async restore(arquivo: string): Promise<RestoreResult> {
    return request<RestoreResult>("/restaurar", {
      method: "POST",
      body: JSON.stringify({ arquivo }),
    });
  },
};

export const authService = {
  async login(email: string, senha: string): Promise<Session> {
    const session = await request<Session>("/auth/login", {
      method: "POST",
      body: JSON.stringify({ email, senha }),
    });
    saveSession(session);
    return session;
  },
  async register(input: {
    nome: string;
    email: string;
    telefone?: string;
    senha: string;
    comoAnfitriao: boolean;
    imovelInicial?: {
      titulo: string;
      descricao: string;
      endereco: {
        rua: string;
        numero: string;
        bairro: string;
        cidade: string;
        estado: string;
        cep: string;
      };
      comodidades: {
        nome: string;
        descricao?: string;
      }[];
      cidade: string;
      valorDiaria: number;
      dataCadastro: string;
      fotos: string[];
      ativo: boolean;
    };
  }): Promise<Session> {
    const session = await request<Session>("/auth/register", {
      method: "POST",
      body: JSON.stringify(input),
    });
    saveSession(session);
    return session;
  },
  async me(): Promise<Usuario> {
    return request<Usuario>("/auth/me");
  },
  logout() {
    clearSession();
  },
};
