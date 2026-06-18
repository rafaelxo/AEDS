import { useEffect, useState } from "react";
import { Navigate, Route, Routes } from "react-router-dom";
import { useStore } from "./app/store";
import { authService, hasSessionToken } from "./services/api";
import AppLayout from "./layouts/AppLayout";
import Landing from "./pages/Landing";
import Explore from "./pages/Explore";
import GuestDashboard from "./pages/GuestDashboard";
import GuestReservations from "./pages/GuestReservations";
import HostDashboard from "./pages/HostDashboard";
import HostListings from "./pages/HostListings";
import HostRevenue from "./pages/HostRevenue";
import HostReservations from "./pages/HostReservations";
import AdminDashboard from "./pages/AdminDashboard";
import AdminUsers from "./pages/AdminUsers";
import AdminProperties from "./pages/AdminProperties";
import AdminReservations from "./pages/AdminReservations";
import AdminAmenities from "./pages/AdminAmenities";
import PropertyDetailOverlay from "./features/properties/PropertyDetailOverlay";

function RoleHome() {
  const user = useStore((s) => s.user);
  if (!user) return <Navigate to="/" replace />;
  if (user.tipo === "ADMIN") return <Navigate to="/admin" replace />;
  if (user.tipo === "ANFITRIAO") return <Navigate to="/host" replace />;
  return <Navigate to="/dashboard" replace />;
}

function ProtectedRoute({ children }: { children: React.ReactNode }) {
  const user = useStore((s) => s.user);
  if (!user) return <Navigate to="/" replace />;
  return <>{children}</>;
}

export default function App() {
  const { user, setUser, logout } = useStore();
  const [booting, setBooting] = useState(true);

  useEffect(() => {
    if (!hasSessionToken()) {
      setBooting(false);
      return;
    }
    authService
      .me()
      .then((me) => {
        setUser(me);
      })
      .catch(() => logout())
      .finally(() => setBooting(false));
  }, []);

  if (booting) {
    return (
      <div
        style={{
          minHeight: "100vh",
          display: "flex",
          alignItems: "center",
          justifyContent: "center",
          background: "var(--canvas)",
        }}
      >
        <div
          className="anim-spin"
          style={{
            width: 28,
            height: 28,
            border: "2.5px solid var(--border)",
            borderTopColor: "var(--accent)",
            borderRadius: "50%",
          }}
        />
      </div>
    );
  }

  return (
    <>
      <Routes>
        <Route
          path="/"
          element={user ? <Navigate to="/go" replace /> : <Landing />}
        />

        <Route path="/go" element={<RoleHome />} />

        <Route
          element={
            <ProtectedRoute>
              <AppLayout />
            </ProtectedRoute>
          }
        >
          <Route path="/explore" element={<Explore />} />

          <Route path="/dashboard" element={<GuestDashboard />} />
          <Route path="/reservations" element={<GuestReservations />} />

          <Route path="/host" element={<HostDashboard />} />
          <Route path="/host/listings" element={<HostListings />} />
          <Route path="/host/revenue" element={<HostRevenue />} />
          <Route path="/host/reservations" element={<HostReservations />} />

          <Route path="/admin" element={<AdminDashboard />} />
          <Route path="/admin/users" element={<AdminUsers />} />
          <Route path="/admin/properties" element={<AdminProperties />} />
          <Route path="/admin/reservations" element={<AdminReservations />} />
          <Route path="/admin/amenities" element={<AdminAmenities />} />
        </Route>

        <Route path="*" element={<Navigate to="/" replace />} />
      </Routes>

      <PropertyDetailOverlay />
    </>
  );
}
