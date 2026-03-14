const autoModeToggle = document.getElementById('autoModeToggle');
const barrierToggle = document.getElementById('barrierToggle');
const barrierStatus = document.getElementById('barrierStatus');
const trespassAlert = document.getElementById('trespassAlert');

autoModeToggle.addEventListener('change', () => {
    const isAuto = autoModeToggle.checked;
    fetch('/setAutoMode?auto=' + (isAuto ? '1' : '0'));
    barrierToggle.disabled = isAuto;
});

barrierToggle.addEventListener('change', () => {
    const isOpen = barrierToggle.checked;
    fetch('/setBarrier?state=' + (isOpen ? 'open' : 'close'));
});

setInterval(async () => {
    try {
        const response = await fetch('/status');
        const data = await response.json();

        autoModeToggle.checked = data.autoMode;
        barrierToggle.disabled = data.autoMode;

        barrierToggle.checked = data.barrierOpen;
        if (data.barrierOpen) {
            barrierStatus.textContent = 'Open';
            barrierStatus.className = 'status-badge open';
        } else {
            barrierStatus.textContent = 'Closed';
            barrierStatus.className = 'status-badge closed';
        }

        if (data.trespassing) {
            trespassAlert.textContent = 'Have Trespassers!';
            trespassAlert.className = 'alert-badge warning';
        } else {
            trespassAlert.textContent = 'Safe';
            trespassAlert.className = 'alert-badge safe';
        }
    } catch (e) {
        console.error('Error fetching data:', e);
    }
}, 1000);
