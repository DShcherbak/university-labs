import Keycloak from "keycloak-js"

const _kc = new Keycloak('/keycloak.json')

const initKeycloak = (onAuthenticatedCallback) =>{
    console.log("geting auth...")
    _kc.init({
        onLoad: 'login-required',
        promiseType: 'native',
        silentCheckSsoRedirectUrl: window.location.origin + '/silent-check-sso.html',
        pkceMethod: 'S256'
    })
        .then((authenticated) => {
            console.log("got auth!" + authenticated)
            if(authenticated){
              onAuthenticatedCallback()
            } else {
              console.log("NO AUTH")
                doLogin();
          }
        })
}

const doLogin = _kc.login;

const doLogout = _kc.logout;

const getToken = () => _kc.token;

const getUsername = () => _kc.tokenParsed?.preferred_username;

const updateToken = (successCallback) =>
    _kc.updateToken(5).then(successCallback).catch(doLogin)

const isAdmin = () => _kc.hasRealmRole("ROLE_ADMIN")

const hasRole = (roles) => roles.some((role) => _kc.hasRealmRole(role));

const UserService= {
    initKeycloak,
    doLogin,
    doLogout,
    getToken,
    isAdmin,
    getUsername,
    updateToken,
    hasRole,
}

export default UserService;