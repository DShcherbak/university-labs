import UserService from './UserService'

export function sendGetRequest(requestUrl) {
    UserService.updateToken()
    const requestOptions = {
        method: 'Get',
        headers: {},
    };
    return fetch(requestUrl, requestOptions)
        .then((response) => {
        if(!response.ok) {console.log("RESPONSE IS BAD:" + response.json()); return undefined}
        else {return response.json();}
    })
}

export function sendChangeRequest(url, type, body){
    UserService.updateToken()
console.log("SENDING: " + url + type + body)
    const requestOptions = {
        method: type,
        headers: {
            'Content-Type': 'application/json',
            'Authorization': `bearer ${UserService.getToken()}`
        },
        body: body
    };
    return fetch(url, requestOptions).then((response) => {
        if (!response.ok) {
            console.log("RESPONSE IS BAD:" + response.json());
            console.error(response.status)
        } else {
            return response.json();
        }
    })
}
export function sendPostRequest(url, body) {
    return sendChangeRequest(url, 'Post', body)
}

export function sendPutRequest(url, body) {
    return sendChangeRequest(url, 'Put', body)
}

export function sendDeleteRequest(url, body) {
    return sendChangeRequest(url, 'Delete', body)
}


