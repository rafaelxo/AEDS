import { useEffect, useState } from "react";
import { MapContainer, TileLayer, Marker, useMap } from "react-leaflet";
import L from "leaflet";
import "leaflet/dist/leaflet.css";
import { MapPin, Shield, Zap, Star, Lock } from "lucide-react";
import AuthPanel from "../features/auth/AuthPanel";
import { imoveisService, type Imovel } from "../services/api";
import { geocodeAddressInput } from "../services/geocoding";
import logoImg from "../assets/logo.png";

const BRAZIL_CENTER: [number, number] = [-15.78, -47.93];

function formatCurrency(v: number) {
  return v.toLocaleString("pt-BR", { style: "currency", currency: "BRL", maximumFractionDigits: 0 });
}

function createPricePin(price: number, selected = false) {
  const label = formatCurrency(price);
  return L.divIcon({
    className: `map-pin ${selected ? "selected" : "accent"}`,
    html: `<div class="map-pin-label">${label}</div>`,
    iconAnchor: [0, 28],
    iconSize: [undefined as any, 28],
  });
}

type GeoProperty = Imovel & { lat: number; lng: number };

export default function Landing() {
  const [properties, setProperties] = useState<GeoProperty[]>([]);
  const [selected, setSelected] = useState<GeoProperty | null>(null);

  useEffect(() => {
    imoveisService.getAll({ ativo: true }).then(async (list) => {
      const results: GeoProperty[] = [];
      for (const p of list) {
        if (p.latitude && p.longitude && Math.abs(p.latitude) > 0.001 && Math.abs(p.longitude) > 0.001) {
          results.push({ ...p, lat: p.latitude, lng: p.longitude });
        } else {
          try {
            await new Promise((r) => setTimeout(r, 250));
            const coords = await geocodeAddressInput(p.endereco, p.cidade);
            if (coords) results.push({ ...p, lat: coords[0], lng: coords[1] });
          } catch {}
        }
      }
      setProperties(results);
    }).catch(() => {});
  }, []);

  return (
    <div style={{ display: "flex", height: "100vh", overflow: "hidden" }}>
      <div
        style={{
          width: "42%",
          minWidth: 380,
          maxWidth: 520,
          height: "100vh",
          overflow: "auto",
          background: "var(--surface)",
          display: "flex",
          flexDirection: "column",
          padding: "0 0 32px",
          boxShadow: "2px 0 40px rgba(12,12,17,0.08)",
          zIndex: 10,
        }}
      >
        <div style={{ padding: "32px 40px 0" }}>
          <div style={{ display: "flex", alignItems: "center", gap: 10 }}>
            <img src={logoImg} alt="Hostly" style={{ width: 36, height: 36, borderRadius: 10, objectFit: "cover" }} />
            <span style={{ fontWeight: 800, fontSize: 20, letterSpacing: "-0.04em", color: "var(--ink)" }}>
              Hostly
            </span>
          </div>
        </div>

        <div style={{ padding: "36px 40px 28px" }}>
          <h1
            style={{
              fontSize: 30,
              fontWeight: 800,
              color: "var(--ink)",
              letterSpacing: "-0.04em",
              lineHeight: 1.18,
              margin: "0 0 10px",
            }}
          >
            Encontre o lugar
            <br />
            <span style={{ color: "var(--accent)" }}>perfeito para ficar</span>
          </h1>
          <p style={{ fontSize: 14, color: "var(--ink-3)", margin: 0, lineHeight: 1.6 }}>
            Explore imóveis em todo o Brasil. Reserve com segurança, sem complicação.
          </p>
        </div>

        <div style={{ padding: "0 40px 28px", display: "flex", flexDirection: "column", gap: 10 }}>
          {[
            { icon: <Shield size={14} />, text: "Pagamento seguro e protegido" },
            { icon: <Zap size={14} />, text: "Confirmação instantânea" },
            { icon: <Star size={14} />, text: "Imóveis verificados por anfitriões" },
          ].map((item, i) => (
            <div key={i} style={{ display: "flex", alignItems: "center", gap: 10, fontSize: 13, color: "var(--ink-3)" }}>
              <span style={{ color: "var(--accent)", display: "flex" }}>{item.icon}</span>
              {item.text}
            </div>
          ))}
        </div>

        <div style={{ height: 1, background: "var(--border)", margin: "0 40px 28px" }} />

        <div style={{ padding: "0 40px", flex: 1 }}>
          <AuthPanel />
        </div>

        <div
          style={{
            margin: "28px 40px 0",
            padding: "12px 16px",
            borderRadius: "var(--radius-md)",
            background: "var(--canvas)",
            border: "1px solid var(--border)",
            display: "flex",
            alignItems: "center",
            gap: 10,
            fontSize: 12,
            color: "var(--ink-3)",
          }}
        >
          <MapPin size={14} style={{ color: "var(--accent)", flexShrink: 0 }} />
          <span>
            {properties.length > 0
              ? `${properties.length} imóvel(is) disponível(is) — explore ao lado →`
              : "Carregando imóveis no mapa..."}
          </span>
        </div>
      </div>

      <div style={{ flex: 1, position: "relative", overflow: "hidden" }}>
        <MapContainer
          center={BRAZIL_CENTER}
          zoom={5}
          style={{ width: "100%", height: "100%" }}
          zoomControl={false}
        >
          <TileLayer
            url="https://{s}.basemaps.cartocdn.com/light_all/{z}/{x}/{y}{r}.png"
            attribution='&copy; <a href="https://carto.com/">CARTO</a>'
            subdomains="abcd"
            maxZoom={19}
          />
          <ZoomControlPosition />
          {properties.map((p) => (
            <Marker
              key={p.idImovel}
              position={[p.lat, p.lng]}
              icon={createPricePin(p.valorDiaria, selected?.idImovel === p.idImovel)}
              eventHandlers={{
                click: () => setSelected(selected?.idImovel === p.idImovel ? null : p),
              }}
            />
          ))}
        </MapContainer>

        <div
          style={{
            position: "absolute",
            top: 16,
            left: 16,
            zIndex: 1000,
            background: "rgba(255,255,255,0.9)",
            backdropFilter: "blur(8px)",
            borderRadius: "var(--radius-md)",
            padding: "8px 14px",
            fontSize: 12,
            fontWeight: 600,
            color: "var(--ink-2)",
            boxShadow: "var(--shadow-sm)",
            display: "flex",
            alignItems: "center",
            gap: 6,
          }}
        >
          <MapPin size={13} style={{ color: "var(--accent)" }} />
          Explore sem precisar entrar
        </div>

        {selected && (
          <LandingPreviewCard
            property={selected}
            onClose={() => setSelected(null)}
          />
        )}
      </div>
    </div>
  );
}

function ZoomControlPosition() {
  const map = useMap();
  useEffect(() => {
    const zc = L.control.zoom({ position: "bottomright" });
    zc.addTo(map);
    return () => { zc.remove(); };
  }, [map]);
  return null;
}

function LandingPreviewCard({ property: p, onClose }: { property: GeoProperty; onClose: () => void }) {
  const photo = p.fotos?.[0];
  return (
    <div
      className="anim-fade-up"
      style={{
        position: "absolute",
        bottom: 24,
        left: "50%",
        transform: "translateX(-50%)",
        zIndex: 1000,
        width: 300,
        background: "var(--surface)",
        borderRadius: "var(--radius-xl)",
        boxShadow: "var(--shadow-xl)",
        overflow: "hidden",
      }}
    >
      {photo && (
        <div style={{ height: 130, overflow: "hidden" }}>
          <img src={photo} alt={p.titulo} style={{ width: "100%", height: "100%", objectFit: "cover" }} />
        </div>
      )}

      <div style={{ padding: "14px 16px 16px" }}>
        <div style={{ fontSize: 14, fontWeight: 700, color: "var(--ink)", marginBottom: 3, lineHeight: 1.3 }}>
          {p.titulo}
        </div>
        <div style={{ fontSize: 12, color: "var(--ink-3)", marginBottom: 12, display: "flex", alignItems: "center", gap: 4 }}>
          <MapPin size={12} style={{ color: "var(--accent)", flexShrink: 0 }} />
          {p.cidade}
        </div>

        <div style={{ position: "relative", marginBottom: 12, height: 22 }}>
          <div style={{ fontSize: 16, fontWeight: 800, color: "var(--accent)", filter: "blur(6px)", userSelect: "none", whiteSpace: "nowrap" }}>
            {formatCurrency(p.valorDiaria)}<span style={{ fontSize: 11, fontWeight: 400, color: "var(--ink-3)" }}>/noite</span>
          </div>
          <div style={{ position: "absolute", inset: 0, display: "flex", alignItems: "center", gap: 5, fontSize: 11, color: "var(--ink-3)", fontWeight: 500 }}>
            <Lock size={11} style={{ flexShrink: 0, color: "var(--ink-4)" }} />
            Faça login para ver o preço
          </div>
        </div>

        {p.comodidades.length > 0 && (
          <div style={{ display: "flex", gap: 4, flexWrap: "wrap", marginBottom: 14, filter: "blur(4px)", userSelect: "none" }}>
            {p.comodidades.slice(0, 3).map((c, i) => (
              <span key={i} style={{ padding: "3px 8px", borderRadius: 99, background: "var(--canvas)", border: "1px solid var(--border)", fontSize: 11, color: "var(--ink-3)" }}>
                {c.nome}
              </span>
            ))}
          </div>
        )}

        <div style={{ padding: "9px 0", textAlign: "center", background: "var(--accent)", color: "#fff", borderRadius: "var(--radius-md)", fontSize: 12, fontWeight: 600 }}>
          Entre para reservar →
        </div>
      </div>

      <button
        onClick={onClose}
        style={{
          position: "absolute",
          top: 10,
          right: 10,
          width: 28,
          height: 28,
          borderRadius: "50%",
          background: "rgba(255,255,255,0.9)",
          border: "none",
          display: "flex",
          alignItems: "center",
          justifyContent: "center",
          boxShadow: "var(--shadow-sm)",
          fontSize: 16,
          color: "var(--ink)",
          lineHeight: 1,
        }}
      >
        ×
      </button>
    </div>
  );
}
