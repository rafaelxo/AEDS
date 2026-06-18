import { useEffect, useRef, useState, useCallback } from "react";
import { MapContainer, TileLayer, Marker, useMap, useMapEvents } from "react-leaflet";
import L from "leaflet";
import "leaflet/dist/leaflet.css";
import type { Imovel } from "../../services/api";
import { useStore } from "../../app/store";
import { geocodeAddressInput } from "../../services/geocoding";

export type GeoProperty = Imovel & { lat: number; lng: number };

function fmt(v: number) {
  return v.toLocaleString("pt-BR", {
    style: "currency",
    currency: "BRL",
    maximumFractionDigits: 0,
  });
}

function makePinIcon(price: number, selected: boolean) {
  return L.divIcon({
    className: `map-pin ${selected ? "selected" : "accent"}`,
    html: `<div class="map-pin-label">${fmt(price)}</div>`,
    iconAnchor: [0, 28],
    iconSize: [undefined as any, 28],
  });
}

function ZoomInit({ center, zoom }: { center: [number, number]; zoom: number }) {
  const map = useMap();
  useEffect(() => {
    map.setView(center, zoom);
    const zc = L.control.zoom({ position: "bottomright" });
    zc.addTo(map);
    return () => { zc.remove(); };
  }, []);
  return null;
}

function MapEvents({ onBoundsChange }: { onBoundsChange?: (b: L.LatLngBounds) => void }) {
  useMapEvents({
    moveend: (e) => onBoundsChange?.(e.target.getBounds()),
    zoomend: (e) => onBoundsChange?.(e.target.getBounds()),
  });
  return null;
}

interface MapViewProps {
  properties: GeoProperty[];
  loading?: boolean;
  onSelect?: (p: GeoProperty | null) => void;
  selectedId?: number | null;
  onBoundsChange?: (b: L.LatLngBounds) => void;
}

export function MapView({ properties, loading, onSelect, selectedId, onBoundsChange }: MapViewProps) {
  const { map: mapState } = useStore();

  return (
    <div style={{ position: "relative", width: "100%", height: "100%" }}>
      <MapContainer
        center={mapState.center}
        zoom={mapState.zoom}
        style={{ width: "100%", height: "100%" }}
        zoomControl={false}
      >
        <TileLayer
          url="https://{s}.basemaps.cartocdn.com/light_all/{z}/{x}/{y}{r}.png"
          attribution='&copy; <a href="https://carto.com/">CARTO</a>'
          subdomains="abcd"
          maxZoom={19}
        />
        <ZoomInit center={mapState.center} zoom={mapState.zoom} />
        <MapEvents onBoundsChange={onBoundsChange} />
        {properties.map((p) => (
          <Marker
            key={p.idImovel}
            position={[p.lat, p.lng]}
            icon={makePinIcon(p.valorDiaria, selectedId === p.idImovel)}
            eventHandlers={{
              click: () => onSelect?.(selectedId === p.idImovel ? null : p),
            }}
          />
        ))}
      </MapContainer>

      {loading && (
        <div
          style={{
            position: "absolute",
            top: 12,
            right: 12,
            zIndex: 1000,
            background: "rgba(255,255,255,0.9)",
            backdropFilter: "blur(6px)",
            borderRadius: "var(--radius-sm)",
            padding: "6px 12px",
            fontSize: 12,
            color: "var(--ink-3)",
            boxShadow: "var(--shadow-sm)",
            display: "flex",
            alignItems: "center",
            gap: 8,
          }}
        >
          <span
            className="anim-spin"
            style={{
              width: 12,
              height: 12,
              border: "2px solid var(--border)",
              borderTopColor: "var(--accent)",
              borderRadius: "50%",
              display: "inline-block",
            }}
          />
          Geocodificando...
        </div>
      )}
    </div>
  );
}

/* Hook: resolves properties to geolocated ones */
export function useGeoProperties(properties: Imovel[]) {
  const [geo, setGeo] = useState<GeoProperty[]>([]);
  const [loading, setLoading] = useState(false);
  const queueRef = useRef<Imovel[]>([]);
  const runningRef = useRef(false);
  const mountedRef = useRef(true);

  const processQueue = useCallback(async () => {
    if (runningRef.current) return;
    runningRef.current = true;
    if (mountedRef.current) setLoading(true);

    while (queueRef.current.length > 0) {
      if (!mountedRef.current) break;
      const p = queueRef.current.shift()!;
      if (
        p.latitude &&
        p.longitude &&
        Math.abs(p.latitude) > 0.001 &&
        Math.abs(p.longitude) > 0.001
      ) {
        if (mountedRef.current) {
          setGeo((prev) => {
            if (prev.find((g) => g.idImovel === p.idImovel)) return prev;
            return [...prev, { ...p, lat: p.latitude!, lng: p.longitude! }];
          });
        }
      } else {
        try {
          await new Promise((r) => setTimeout(r, 280));
          if (!mountedRef.current) break;
          const coords = await geocodeAddressInput(p.endereco, p.cidade);
          if (coords && mountedRef.current) {
            setGeo((prev) => {
              if (prev.find((g) => g.idImovel === p.idImovel)) return prev;
              return [...prev, { ...p, lat: coords[0], lng: coords[1] }];
            });
          }
        } catch {}
      }
    }

    runningRef.current = false;
    if (mountedRef.current) setLoading(false);
  }, []);

  useEffect(() => {
    mountedRef.current = true;
    return () => { mountedRef.current = false; };
  }, []);

  useEffect(() => {
    if (!properties.length) {
      setGeo([]);
      return;
    }
    setGeo([]);
    queueRef.current = [...properties];
    processQueue();
  }, [properties.map((p) => p.idImovel).join(",")]);

  return { geo, loading };
}
