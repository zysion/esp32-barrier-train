const autoModeToggle = document.getElementById('autoModeToggle');
const barrierToggle = document.getElementById('barrierToggle');
const barrierStatus = document.getElementById('barrierStatus');
const trespassAlert = document.getElementById('trespassAlert');
const barrierControlGroup = barrierToggle.closest('.control-group');

function setBarrierControlEnabled(isEnabled) {
    barrierToggle.disabled = !isEnabled;
    barrierControlGroup?.classList.toggle('disabled', !isEnabled);
}

autoModeToggle.addEventListener('change', () => {
    const isAuto = autoModeToggle.checked;
    fetch('/setAutoMode?auto=' + (isAuto ? '1' : '0'));
    setBarrierControlEnabled(!isAuto);
});

barrierToggle.addEventListener('change', () => {
    if (autoModeToggle.checked) {
        return;
    }

    const isOpen = barrierToggle.checked;
    fetch('/setBarrier?state=' + (isOpen ? 'open' : 'close'));
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
