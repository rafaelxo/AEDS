import { useEffect, useState } from "react";
import {
  X,
  ChevronLeft,
  ChevronRight,
  MapPin,
  Check,
  CreditCard,
  Banknote,
  Smartphone,
} from "lucide-react";
import { imoveisService, reservaService, type Imovel, type Reserva } from "../../services/api";
import { useStore } from "../../app/store";

function fmt(v: number) {
  return v.toLocaleString("pt-BR", { style: "currency", currency: "BRL", maximumFractionDigits: 0 });
}

type PayMethod = Reserva["formaPagamento"];

const PAYMENT_OPTIONS: { value: PayMethod; label: string; icon: React.ReactNode }[] = [
  { value: "PIX", label: "PIX", icon: <Smartphone size={14} /> },
  { value: "CARTAO_CREDITO", label: "Cartão de crédito", icon: <CreditCard size={14} /> },
  { value: "CARTAO_DEBITO", label: "Cartão de débito", icon: <CreditCard size={14} /> },
  { value: "BOLETO", label: "Boleto", icon: <Banknote size={14} /> },
  { value: "DINHEIRO", label: "Dinheiro", icon: <Banknote size={14} /> },
];

export default function PropertyDetailOverlay() {
  const { detailPropertyId, closeDetail } = useStore();
  if (!detailPropertyId) return null;

  return (
    <>
      <div className="overlay-backdrop" onClick={closeDetail} />
      <div className="overlay-panel">
        <PropertyDetail id={detailPropertyId} onClose={closeDetail} />
      </div>
    </>
  );
}

function PropertyDetail({ id, onClose }: { id: number; onClose: () => void }) {
  const { user } = useStore();
  const [property, setProperty] = useState<Imovel | null>(null);
  const [loading, setLoading] = useState(true);
  const [photoIdx, setPhotoIdx] = useState(0);

  /* booking state */
  const [checkIn, setCheckIn] = useState("");
  const [checkOut, setCheckOut] = useState("");
  const [payMethod, setPayMethod] = useState<PayMethod>("PIX");
  const [booking, setBooking] = useState<"idle" | "loading" | "success" | "error">("idle");
  const [bookingError, setBookingError] = useState<string | null>(null);

  useEffect(() => {
    setLoading(true);
    imoveisService
      .getById(id)
      .then(setProperty)
      .catch(() => {})
      .finally(() => setLoading(false));
  }, [id]);

  /* Close on Escape */
  useEffect(() => {
    const handler = (e: KeyboardEvent) => { if (e.key === "Escape") onClose(); };
    document.addEventListener("keydown", handler);
    return () => document.removeEventListener("keydown", handler);
  }, [onClose]);

  if (loading) {
    return (
      <div
        style={{
          width: "min(860px, 96vw)",
          background: "var(--surface)",
          borderRadius: "var(--radius-2xl)",
          padding: 64,
          display: "flex",
          alignItems: "center",
          justifyContent: "center",
          minHeight: 400,
        }}
      >
        <div
          className="anim-spin"
          style={{
            width: 32,
            height: 32,
            border: "3px solid var(--border)",
            borderTopColor: "var(--accent)",
            borderRadius: "50%",
          }}
        />
      </div>
    );
  }

  if (!property) return null;

  const p = property;
  const photos = p.fotos ?? [];
  const currentPhoto = photos[photoIdx];
  const nights =
    checkIn && checkOut
      ? Math.max(
          0,
          Math.round(
            (new Date(checkOut).getTime() - new Date(checkIn).getTime()) / 86400000,
          ),
        )
      : 0;
  const total = nights * p.valorDiaria;

  const handleBook = async () => {
    if (!user || !checkIn || !checkOut || nights < 1) return;
    setBooking("loading");
    setBookingError(null);
    try {
      const reserva = await reservaService.create({
        idImovel: p.idImovel,
        idHospede: user.idUsuario,
        dataInicio: checkIn,
        dataFim: checkOut,
        formaPagamento: payMethod,
      });
      await reservaService.confirm(reserva.idReserva, payMethod);
      setBooking("success");
    } catch (e) {
      setBookingError(friendlyBookingError(e instanceof Error ? e.message : ""));
      setBooking("error");
    }
  };

  return (
    <div
      className="anim-fade-up"
      style={{
        width: "min(900px, 96vw)",
        background: "var(--surface)",
        borderRadius: "var(--radius-2xl)",
        overflow: "hidden",
        boxShadow: "var(--shadow-2xl)",
        display: "flex",
        flexDirection: "column",
      }}
      onClick={(e) => e.stopPropagation()}
    >

      <div style={{ position: "relative", height: 340, background: "var(--surface-dim)", flexShrink: 0 }}>
        {currentPhoto ? (
          <img
            src={currentPhoto}
            alt={p.titulo}
            style={{ width: "100%", height: "100%", objectFit: "cover", display: "block" }}
          />
        ) : (
          <div
            style={{
              width: "100%",
              height: "100%",
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              background: "linear-gradient(135deg, #F0EDE8 0%, #E8E4DC 100%)",
            }}
          >
            <MapPin size={48} style={{ color: "var(--ink-5)" }} />
          </div>
        )}

        <button
          onClick={onClose}
          style={{
            position: "absolute",
            top: 16,
            left: 16,
            width: 36,
            height: 36,
            borderRadius: "50%",
            background: "rgba(255,255,255,0.92)",
            border: "none",
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
            boxShadow: "var(--shadow-sm)",
            zIndex: 2,
          }}
        >
          <X size={16} style={{ color: "var(--ink)" }} />
        </button>

        {photos.length > 1 && (
          <>
            <button
              onClick={() => setPhotoIdx((i) => (i - 1 + photos.length) % photos.length)}
              style={{
                position: "absolute",
                left: 16,
                top: "50%",
                transform: "translateY(-50%)",
                width: 36,
                height: 36,
                borderRadius: "50%",
                background: "rgba(255,255,255,0.92)",
                border: "none",
                display: "flex",
                alignItems: "center",
                justifyContent: "center",
                boxShadow: "var(--shadow-sm)",
              }}
            >
              <ChevronLeft size={16} style={{ color: "var(--ink)" }} />
            </button>
            <button
              onClick={() => setPhotoIdx((i) => (i + 1) % photos.length)}
              style={{
                position: "absolute",
                right: 16,
                top: "50%",
                transform: "translateY(-50%)",
                width: 36,
                height: 36,
                borderRadius: "50%",
                background: "rgba(255,255,255,0.92)",
                border: "none",
                display: "flex",
                alignItems: "center",
                justifyContent: "center",
                boxShadow: "var(--shadow-sm)",
              }}
            >
              <ChevronRight size={16} style={{ color: "var(--ink)" }} />
            </button>

            <div
              style={{
                position: "absolute",
                bottom: 14,
                left: "50%",
                transform: "translateX(-50%)",
                display: "flex",
                gap: 6,
              }}
            >
              {photos.map((_, i) => (
                <button
                  key={i}
                  onClick={() => setPhotoIdx(i)}
                  style={{
                    width: i === photoIdx ? 20 : 7,
                    height: 7,
                    borderRadius: "99px",
                    background: i === photoIdx ? "#fff" : "rgba(255,255,255,0.5)",
                    border: "none",
                    padding: 0,
                    transition: "all 200ms ease",
                  }}
                />
              ))}
            </div>
          </>
        )}
      </div>

      <div style={{ display: "flex", gap: 0, overflow: "hidden" }}>
        <div
          style={{
            flex: 1,
            overflowY: "auto",
            padding: "28px 32px",
          }}
        >
          <div style={{ marginBottom: 20 }}>
            <h1
              style={{
                fontSize: 22,
                fontWeight: 800,
                color: "var(--ink)",
                letterSpacing: "-0.03em",
                margin: "0 0 6px",
              }}
            >
              {p.titulo}
            </h1>
            <div
              style={{
                display: "flex",
                alignItems: "center",
                gap: 6,
                fontSize: 13,
                color: "var(--ink-3)",
              }}
            >
              <MapPin size={13} style={{ color: "var(--accent)" }} />
              {p.endereco.rua}, {p.endereco.numero} · {p.endereco.bairro} · {p.cidade} · {p.endereco.estado}
            </div>
          </div>

          <div
            style={{
              display: "flex",
              gap: 24,
              paddingBottom: 20,
              borderBottom: "1px solid var(--border)",
              marginBottom: 20,
            }}
          >
            <StatChip label="Diária" value={fmt(p.valorDiaria)} />
            <StatChip label="Comodidades" value={String(p.comodidades.length)} />
            <StatChip label="Status" value={p.ativo ? "Disponível" : "Indisponível"} />
          </div>

          {p.descricao && (
            <div style={{ marginBottom: 24 }}>
              <SectionLabel>Sobre o imóvel</SectionLabel>
              <p style={{ fontSize: 14, color: "var(--ink-2)", lineHeight: 1.7, margin: 0 }}>
                {p.descricao}
              </p>
            </div>
          )}

          {p.comodidades.length > 0 && (
            <div style={{ marginBottom: 24 }}>
              <SectionLabel>Comodidades</SectionLabel>
              <div style={{ display: "flex", flexWrap: "wrap", gap: 8 }}>
                {p.comodidades.map((c, i) => (
                  <span
                    key={i}
                    style={{
                      display: "flex",
                      alignItems: "center",
                      gap: 6,
                      padding: "6px 12px",
                      borderRadius: "99px",
                      background: "var(--canvas)",
                      border: "1px solid var(--border)",
                      fontSize: 12,
                      color: "var(--ink-2)",
                      fontWeight: 500,
                    }}
                  >
                    <Check size={11} style={{ color: "var(--green)" }} />
                    {c.nome}
                  </span>
                ))}
              </div>
            </div>
          )}

          <div>
            <SectionLabel>Localização</SectionLabel>
            <div
              style={{
                padding: "14px 16px",
                borderRadius: "var(--radius-md)",
                background: "var(--canvas)",
                border: "1px solid var(--border)",
                fontSize: 13,
                color: "var(--ink-2)",
                lineHeight: 1.7,
              }}
            >
              {p.endereco.rua}, {p.endereco.numero}
              <br />
              {p.endereco.bairro} · {p.cidade} · {p.endereco.estado}
              <br />
              CEP {p.endereco.cep}
            </div>
          </div>
        </div>

        <div
          style={{
            width: 320,
            minWidth: 320,
            padding: "28px 24px",
            borderLeft: "1px solid var(--border)",
            display: "flex",
            flexDirection: "column",
            gap: 16,
          }}
        >
          <div>
            <div style={{ fontSize: 22, fontWeight: 800, color: "var(--accent)", letterSpacing: "-0.03em" }}>
              {fmt(p.valorDiaria)}
            </div>
            <div style={{ fontSize: 12, color: "var(--ink-3)" }}>por noite</div>
          </div>

          {!user ? (
            <div
              style={{
                padding: "16px",
                borderRadius: "var(--radius-md)",
                background: "var(--canvas)",
                border: "1px solid var(--border)",
                textAlign: "center",
                fontSize: 13,
                color: "var(--ink-3)",
              }}
            >
              Faça login para reservar
            </div>
          ) : booking === "success" ? (
            <div
              style={{
                padding: "20px",
                borderRadius: "var(--radius-md)",
                background: "var(--green-tint)",
                border: "1px solid var(--green)",
                textAlign: "center",
              }}
            >
              <Check size={28} style={{ color: "var(--green)", margin: "0 auto 8px" }} />
              <div style={{ fontSize: 14, fontWeight: 700, color: "var(--green)" }}>Reserva confirmada!</div>
              <div style={{ fontSize: 12, color: "var(--ink-3)", marginTop: 4 }}>
                Acesse Minhas Reservas para detalhes.
              </div>
            </div>
          ) : (
            <>
              <div
                style={{
                  border: "1.5px solid var(--border)",
                  borderRadius: "var(--radius-md)",
                  overflow: "hidden",
                }}
              >
                <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr" }}>
                  <div style={{ padding: "10px 12px", borderRight: "1px solid var(--border)" }}>
                    <div style={{ fontSize: 10, fontWeight: 700, color: "var(--ink-3)", textTransform: "uppercase", letterSpacing: "0.05em", marginBottom: 4 }}>
                      Check-in
                    </div>
                    <input
                      type="date"
                      value={checkIn}
                      min={new Date().toISOString().slice(0, 10)}
                      onChange={(e) => setCheckIn(e.target.value)}
                      style={{
                        border: "none",
                        background: "transparent",
                        fontSize: 13,
                        color: "var(--ink)",
                        fontFamily: "inherit",
                        width: "100%",
                        padding: 0,
                        outline: "none",
                      }}
                    />
                  </div>
                  <div style={{ padding: "10px 12px" }}>
                    <div style={{ fontSize: 10, fontWeight: 700, color: "var(--ink-3)", textTransform: "uppercase", letterSpacing: "0.05em", marginBottom: 4 }}>
                      Check-out
                    </div>
                    <input
                      type="date"
                      value={checkOut}
                      min={checkIn || new Date().toISOString().slice(0, 10)}
                      onChange={(e) => setCheckOut(e.target.value)}
                      style={{
                        border: "none",
                        background: "transparent",
                        fontSize: 13,
                        color: "var(--ink)",
                        fontFamily: "inherit",
                        width: "100%",
                        padding: 0,
                        outline: "none",
                      }}
                    />
                  </div>
                </div>
              </div>

              <div>
                <div style={{ fontSize: 11, fontWeight: 600, color: "var(--ink-3)", textTransform: "uppercase", letterSpacing: "0.06em", marginBottom: 8 }}>
                  Pagamento
                </div>
                <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 6 }}>
                  {PAYMENT_OPTIONS.map((opt) => (
                    <button
                      key={opt.value}
                      onClick={() => setPayMethod(opt.value)}
                      style={{
                        display: "flex",
                        alignItems: "center",
                        gap: 8,
                        padding: "8px 12px",
                        borderRadius: "var(--radius-sm)",
                        border: `1.5px solid ${payMethod === opt.value ? "var(--accent)" : "var(--border)"}`,
                        background: payMethod === opt.value ? "var(--accent-tint)" : "transparent",
                        color: payMethod === opt.value ? "var(--accent)" : "var(--ink-3)",
                        fontSize: 12,
                        fontWeight: 600,
                        textAlign: "left",
                        transition: "all 120ms ease",
                        gridColumn: opt.value === "DINHEIRO" ? "1 / -1" : undefined,
                      }}
                    >
                      {opt.icon}
                      {opt.label}
                    </button>
                  ))}
                </div>
              </div>

              {nights > 0 && (
                <div
                  style={{
                    padding: "12px 14px",
                    borderRadius: "var(--radius-md)",
                    background: "var(--canvas)",
                    border: "1px solid var(--border)",
                    display: "flex",
                    flexDirection: "column",
                    gap: 6,
                  }}
                >
                  <div style={{ display: "flex", justifyContent: "space-between", fontSize: 12, color: "var(--ink-3)" }}>
                    <span>
                      {fmt(p.valorDiaria)} × {nights} {nights === 1 ? "noite" : "noites"}
                    </span>
                    <span>{fmt(total)}</span>
                  </div>
                  <div
                    style={{
                      display: "flex",
                      justifyContent: "space-between",
                      fontSize: 14,
                      fontWeight: 700,
                      color: "var(--ink)",
                      paddingTop: 8,
                      borderTop: "1px solid var(--border)",
                    }}
                  >
                    <span>Total</span>
                    <span style={{ color: "var(--accent)" }}>{fmt(total)}</span>
                  </div>
                </div>
              )}

              {bookingError && (
                <div
                  style={{
                    padding: "10px 12px",
                    borderRadius: "var(--radius-sm)",
                    background: "var(--red-tint)",
                    color: "var(--red)",
                    fontSize: 12,
                    fontWeight: 500,
                  }}
                >
                  {bookingError}
                </div>
              )}

              <button
                onClick={handleBook}
                disabled={!checkIn || !checkOut || nights < 1 || booking === "loading" || !p.ativo}
                className="btn btn-primary"
                style={{ width: "100%", justifyContent: "center", padding: "12px" }}
              >
                {booking === "loading" ? "Reservando..." : p.ativo ? "Reservar agora" : "Imóvel indisponível"}
              </button>

              {!p.ativo && (
                <p style={{ fontSize: 11, color: "var(--ink-4)", textAlign: "center", margin: 0 }}>
                  Este imóvel não está disponível para reservas no momento.
                </p>
              )}
            </>
          )}
        </div>
      </div>
    </div>
  );
}

function friendlyBookingError(raw: string): string {
  const m = raw.toLowerCase();
  if (m === "network_error" || m.includes("network_error") || m.includes("failed to fetch"))
    return "Sem conexão com o servidor. Verifique sua internet e tente novamente.";
  if (m.includes("400") || m.includes("invalid") || m.includes("inválid"))
    return "Datas inválidas ou imóvel indisponível para o período selecionado.";
  if (m.includes("401") || m.includes("403") || m.includes("unauthorized"))
    return "Sessão expirada. Faça logout e entre novamente.";
  if (m.includes("404"))
    return "Imóvel não encontrado. Tente atualizar a página.";
  if (m.includes("409") || m.includes("conflict") || m.includes("unavailable") || m.includes("reservad"))
    return "Este imóvel já está reservado no período escolhido. Tente outras datas.";
  if (m.includes("500") || m.includes("internal"))
    return "Erro interno do servidor. Tente novamente em instantes.";
  if (!raw) return "Não foi possível concluir a reserva. Tente novamente.";
  return raw;
}

function SectionLabel({ children }: { children: React.ReactNode }) {
  return (
    <div
      style={{
        fontSize: 11,
        fontWeight: 700,
        color: "var(--ink-3)",
        textTransform: "uppercase",
        letterSpacing: "0.08em",
        marginBottom: 10,
      }}
    >
      {children}
    </div>
  );
}

function StatChip({ label, value }: { label: string; value: string }) {
  return (
    <div>
      <div style={{ fontSize: 10, color: "var(--ink-4)", fontWeight: 600, textTransform: "uppercase", letterSpacing: "0.06em", marginBottom: 2 }}>
        {label}
      </div>
      <div style={{ fontSize: 15, fontWeight: 700, color: "var(--ink)" }}>{value}</div>
    </div>
  );
}
