export function sendGetRequest(requestUrl){
    const requestOptions = {
        method: 'Get',
        headers: {},
    };
    return fetch(requestUrl, requestOptions).then(response => response.json())
        .then((responseData) => {
            return responseData;
        })
}

export function sendCoolGetRequest(requestUrl) {
    const requestOptions = {
        method: 'Get',
        headers: {},
    };
    return fetch(requestUrl, requestOptions)
        .then((response) => {
        if(!response.ok) {console.log("RESPONSE IS BAD:" + response); throw new Error(response.status)}
        else {console.log("RESPONSE IS OK:" + response); return response.json();}
    })
}

export function sendCoolChangeRequest(url, type, body){

    const requestOptions = {
        method: 'type',
        headers: { 'Content-Type': 'application/json' },
        body: body
    };
    return fetch(url, requestOptions).then((response) => {
        if (!response.ok) {
            console.log("RESPONSE IS BAD:" + response);
            throw new Error(response.status)
        } else {
            console.log("RESPONSE IS OK:" + response);
            return response.json();
        }
    })
}
export function sendPostRequest(url, body) {
    return  sendChangeRequest(url, 'Post', body)
}

export function sendPutRequest(url, body) {
    return  sendChangeRequest(url, 'Put', body)
}

export function sendDeleteRequest(url, body) {
    return  sendChangeRequest(url, 'Delete', body)
}

function sendChangeRequest(url, type, body){

    const requestOptions = {
        method: 'type',
        headers: { 'Content-Type': 'application/json' },
        body: body
    };
    return fetch(url, requestOptions).then(response => response.json())
        .then((responseData) => {
            return responseData;
        })
}