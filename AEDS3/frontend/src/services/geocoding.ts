import type { Imovel } from "./api";

type GeocodeCandidate = {
  lat: string;
  lon: string;
  importance?: number;
  place_rank?: number;
  address?: {
    city?: string;
    town?: string;
    village?: string;
    state?: string;
    postcode?: string;
    road?: string;
  };
};

type Coords = [number, number];

export type AddressInput = {
  rua?: string;
  numero?: string;
  bairro?: string;
  cidade?: string;
  estado?: string;
  cep?: string;
};

const geocodeCache = new Map<string, Coords>();

const normalize = (value?: string) =>
  (value ?? "")
    .normalize("NFD")
    .replace(/\p{Diacritic}/gu, "")
    .trim()
    .toLowerCase();

const normalizeCep = (value?: string) => (value ?? "").replace(/\D/g, "");

const cityFromCandidate = (candidate: GeocodeCandidate) =>
  candidate.address?.city ??
  candidate.address?.town ??
  candidate.address?.village ??
  "";

const scoreCandidate = (
  candidate: GeocodeCandidate,
  target: {
    city?: string;
    state?: string;
    street?: string;
    postcode?: string;
  },
) => {
  let score = 0;

  const targetCity = normalize(target.city);
  const targetState = normalize(target.state);
  const targetStreet = normalize(target.street);
  const targetPostcode = normalizeCep(target.postcode);

  const candCity = normalize(cityFromCandidate(candidate));
  const candState = normalize(candidate.address?.state);
  const candStreet = normalize(candidate.address?.road);
  const candPostcode = normalizeCep(candidate.address?.postcode);

  if (targetCity && candCity && targetCity === candCity) score += 40;
  if (targetState && candState && targetState === candState) score += 25;
  if (targetStreet && candStreet && candStreet.includes(targetStreet))
    score += 20;
  if (targetPostcode && candPostcode && targetPostcode === candPostcode)
    score += 60;

  score += (candidate.importance ?? 0) * 20;
  score += (candidate.place_rank ?? 0) / 10;

  return score;
};

async function fetchCandidates(url: string): Promise<GeocodeCandidate[]> {
  const response = await fetch(url);
  if (!response.ok) return [];

  const data = (await response.json()) as GeocodeCandidate[];
  return Array.isArray(data) ? data : [];
}

function bestCoords(
  candidates: GeocodeCandidate[],
  target: {
    city?: string;
    state?: string;
    street?: string;
    postcode?: string;
  },
): Coords | null {
  if (!candidates.length) return null;

  const sorted = [...candidates].sort(
    (a, b) => scoreCandidate(b, target) - scoreCandidate(a, target),
  );

  const best = sorted[0];
  const lat = Number(best.lat);
  const lon = Number(best.lon);
  if (!Number.isFinite(lat) || !Number.isFinite(lon)) return null;

  return [lat, lon];
}

export async function geocodeFreeText(query: string): Promise<Coords | null> {
  const normalized = query.trim();
  if (!normalized) return null;

  const cacheKey = `free:${normalize(normalized)}`;
  const cached = geocodeCache.get(cacheKey);
  if (cached) return cached;

  const url =
    `https://nominatim.openstreetmap.org/search?format=jsonv2&addressdetails=1&countrycodes=br&limit=8&dedupe=1` +
    `&q=${encodeURIComponent(normalized)}`;

  const candidates = await fetchCandidates(url);
  const coords = bestCoords(candidates, {});
  if (coords) {
    geocodeCache.set(cacheKey, coords);
  }

  return coords;
}

export async function geocodePropertyAddress(
  imovel: Imovel,
): Promise<Coords | null> {
  if (
    Number.isFinite(imovel.latitude) &&
    Number.isFinite(imovel.longitude) &&
    Math.abs(imovel.latitude ?? 0) > 0 &&
    Math.abs(imovel.longitude ?? 0) > 0
  ) {
    return [imovel.latitude as number, imovel.longitude as number];
  }

  const address = imovel.endereco;
  const city = address?.cidade || imovel.cidade;
  const state = address?.estado;
  const street = [address?.rua, address?.numero].filter(Boolean).join(" ");
  const postcode = address?.cep;

  const cacheKey = `prop:${imovel.idImovel}:${normalize(street)}:${normalize(city)}:${normalize(state)}:${normalizeCep(postcode)}`;
  const cached = geocodeCache.get(cacheKey);
  if (cached) return cached;

  const candidatesSets: GeocodeCandidate[][] = [];

  const cep = normalizeCep(postcode);
  if (cep.length >= 8) {
    const byCep = `https://nominatim.openstreetmap.org/search?format=jsonv2&addressdetails=1&countrycodes=br&limit=8&postalcode=${encodeURIComponent(cep)}`;
    candidatesSets.push(await fetchCandidates(byCep));
  }

  const params = new URLSearchParams({
    format: "jsonv2",
    addressdetails: "1",
    countrycodes: "br",
    limit: "8",
    dedupe: "1",
  });

  if (street) params.set("street", street);
  if (city) params.set("city", city);
  if (state) params.set("state", state);
  if (cep) params.set("postalcode", cep);

  const structured = `https://nominatim.openstreetmap.org/search?${params.toString()}`;
  candidatesSets.push(await fetchCandidates(structured));

  const fullAddress = [street, address?.bairro, city, state, "Brasil"]
    .filter(Boolean)
    .join(", ");
  const byQuery = `https://nominatim.openstreetmap.org/search?format=jsonv2&addressdetails=1&countrycodes=br&limit=8&dedupe=1&q=${encodeURIComponent(fullAddress)}`;
  candidatesSets.push(await fetchCandidates(byQuery));

  const fallbackCity = [city, state, "Brasil"].filter(Boolean).join(", ");
  if (fallbackCity) {
    const cityQuery = `https://nominatim.openstreetmap.org/search?format=jsonv2&addressdetails=1&countrycodes=br&limit=8&dedupe=1&q=${encodeURIComponent(fallbackCity)}`;
    candidatesSets.push(await fetchCandidates(cityQuery));
  }

  const merged = candidatesSets.flat();
  const coords = bestCoords(merged, { city, state, street, postcode });
  if (coords) {
    geocodeCache.set(cacheKey, coords);
  }

  return coords;
}

export async function geocodeAddressInput(
  address: AddressInput,
  fallbackCity?: string,
): Promise<Coords | null> {
  const fakeProperty = {
    idImovel: 0,
    idUsuario: 0,
    titulo: "",
    descricao: "",
    endereco: {
      rua: address.rua ?? "",
      numero: address.numero ?? "",
      bairro: address.bairro ?? "",
      cidade: address.cidade ?? fallbackCity ?? "",
      estado: address.estado ?? "",
      cep: address.cep ?? "",
    },
    comodidades: [],
    cidade: address.cidade ?? fallbackCity ?? "",
    valorDiaria: 0,
    dataCadastro: "",
    fotos: [],
    ativo: true,
  } as Imovel;

  return geocodePropertyAddress(fakeProperty);
}
