

// src/components/logout-button.js

import React from "react";
import { useAuth0 } from "@auth0/auth0-react";
import UserService from "../services/UserService";

const LogoutButton = () => {
  return (
    <button
      className="btn btn-danger btn-block"
      onClick={() =>
          UserService.doLogout()
      }
    >
        Log out
    </button>
  );
};

export default LogoutButton;


