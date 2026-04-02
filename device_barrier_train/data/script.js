const autoModeToggle = document.getElementById('autoModeToggle');
const barrierToggle = document.getElementById('barrierToggle');
const barrierStatus = document.getElementById('barrierStatus');
const trespassAlert = document.getElementById('trespassAlert');
const barrierControlGroup = barrierToggle.closest('.control-group');




// websocket connection
const ws = new WebSocket('ws://' + window.location.host + '/ws');

ws.onopen = () => {
    console.log('WebSocket connection established');
}
ws.onclose = () => {
    console.log('WebSocket connection closed');
}
ws.onerror = (error) => {
    console.error('WebSocket error:', error);
}

ws.onmessage = (event) => {
    const data = JSON.parse(event.data);
    const type = data.type;

    if(type === 'barrierstatus') {
        console.log('Received barrier status update:', data.value);
        if(data.value === 'open') {
            barrierStatus.textContent = 'Open';
            barrierStatus.className = 'status-badge open';
        } else {
            barrierStatus.textContent = 'Closed';
            barrierStatus.className = 'status-badge closed';
        }
    }
    else if(type === 'alert') {
        console.log('Received alert status:', data.value);
        if(data.value === 'DANGER') {
            trespassAlert.textContent = 'Danger!';
            // Used warning class since danger class does not exist in style.css
            trespassAlert.className = 'alert-badge warning';
        } else {
            trespassAlert.textContent = 'Safe';
            trespassAlert.className = 'alert-badge safe';
        }
    }
}

// logic function
function setBarrierControlEnabled(isEnabled) {
    barrierToggle.disabled = !isEnabled;
    if (barrierControlGroup) {
        if (isEnabled) {
            barrierControlGroup.classList.remove('disabled');
        } else {
            barrierControlGroup.classList.add('disabled');
        }
    }
}

// Initialize state on load
setBarrierControlEnabled(!autoModeToggle.checked);

autoModeToggle.addEventListener('change', () => {
    const isAuto = autoModeToggle.checked;
    //fetch('/setAutoMode?auto=' + (isAuto ? '1' : '0'));
    setBarrierControlEnabled(!isAuto);
    if(ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({ type: 'Mode', mode: isAuto ? 'AUTO' : 'MANUAL' }));
        console.log('sent mode change to circuit via websocket');
    }
});

barrierToggle.addEventListener('change', () => {
    if (autoModeToggle.checked) {
        return;
    }

    const isOpen = barrierToggle.checked;
    //fetch('/setBarrier?state=' + (isOpen ? 'open' : 'close'));

    if(ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({ type: 'barrier_status', action: isOpen ? 'open' : 'close' }));
        console.log('sent barrier control command via websocket');
    }
});

setInterval(async () => {
    try {
        const response = await fetch('/status');
        const data = await response.json();

        autoModeToggle.checked = data.autoMode;
        setBarrierControlEnabled(!data.autoMode);

        barrierToggle.checked = data.barrierOpen;
        if (data.barrierOpen) {
            barrierStatus.textContent = 'Open';
            barrierStatus.className = 'status-badge open';
        } else {
            barrierStatus.textContent = 'Closed';
            barrierStatus.className = 'status-badge closed';
        }
    } catch (e) {
        console.error('Error fetching data:', e);
    }
}, 1000);