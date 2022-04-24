

// src/components/authentication-button.js

import React from "react";

import LoginButton from "./login-button";
import LogoutButton from "./logout-button";

import { useAuth0 } from "@auth0/auth0-react";
import UserService from "../services/UserService";

const AuthenticationButton = () => {
  return <LogoutButton />
};

export default AuthenticationButton;


