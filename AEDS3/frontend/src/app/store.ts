import { create } from "zustand";
import { persist } from "zustand/middleware";
import type { Usuario } from "../services/api";

interface MapState {
  center: [number, number];
  zoom: number;
  selectedPropertyId: number | null;
}

interface FilterState {
  priceMin: number;
  priceMax: number;
  amenityIds: number[];
  search: string;
}

interface AppStore {
  user: Usuario | null;
  token: string | null;
  sidebarCollapsed: boolean;
  searchAlgo: "bm" | "kmp";
  map: MapState;
  filters: FilterState;
  detailPropertyId: number | null;
  bookingPropertyId: number | null;

  setUser: (user: Usuario | null) => void;
  setToken: (token: string | null) => void;
  logout: () => void;
  setSidebarCollapsed: (v: boolean) => void;
  setSearchAlgo: (algo: "bm" | "kmp") => void;
  setMapCenter: (center: [number, number], zoom?: number) => void;
  setSelectedProperty: (id: number | null) => void;
  setFilters: (f: Partial<FilterState>) => void;
  resetFilters: () => void;
  openDetail: (id: number) => void;
  closeDetail: () => void;
  openBooking: (id: number) => void;
  closeBooking: () => void;
}

const DEFAULT_FILTERS: FilterState = {
  priceMin: 0,
  priceMax: 5000,
  amenityIds: [],
  search: "",
};

export const useStore = create<AppStore>()(
  persist(
    (set) => ({
      user: null,
      token: null,
      sidebarCollapsed: false,
      searchAlgo: "bm" as "bm" | "kmp",
      map: {
        center: [-14.235, -51.925],
        zoom: 5,
        selectedPropertyId: null,
      },
      filters: DEFAULT_FILTERS,
      detailPropertyId: null,
      bookingPropertyId: null,

      setUser: (user) => set({ user }),
      setToken: (token) => set({ token }),
      logout: () => {
        localStorage.removeItem("hostly_token");
        set({ user: null, token: null, detailPropertyId: null });
      },
      setSidebarCollapsed: (v) => set({ sidebarCollapsed: v }),
      setSearchAlgo: (algo) => set({ searchAlgo: algo }),
      setMapCenter: (center, zoom) =>
        set((s) => ({ map: { ...s.map, center, zoom: zoom ?? s.map.zoom } })),
      setSelectedProperty: (id) =>
        set((s) => ({ map: { ...s.map, selectedPropertyId: id } })),
      setFilters: (f) =>
        set((s) => ({ filters: { ...s.filters, ...f } })),
      resetFilters: () => set({ filters: DEFAULT_FILTERS }),
      openDetail: (id) => set({ detailPropertyId: id }),
      closeDetail: () => set({ detailPropertyId: null }),
      openBooking: (id) => set({ bookingPropertyId: id }),
      closeBooking: () => set({ bookingPropertyId: null }),
    }),
    {
      name: "hostly-app",
      partialize: (s) => ({
        token: s.token,
        sidebarCollapsed: s.sidebarCollapsed,
        searchAlgo: s.searchAlgo,
      }),
    },
  ),
);
