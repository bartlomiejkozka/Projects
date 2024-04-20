function formatTime(delta) {
    const days = Math.floor(delta / (1000 * 60 * 60 * 24));
    const hours = Math.floor((delta % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
    const minutes = Math.floor((delta % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((delta % (1000 * 60)) / 1000);

    return `${days} dni : ${hours} godzin : ${minutes} minut : ${seconds} sekund`;
}

function setTime(d){
    const date = new Date();
    const delta = d - date;
    const fomrated = formatTime(delta);
    document.getElementById("time").textContent = fomrated; 
    document.getElementById("time").style.fontSize = "25px"
}

const d = new Date(2024, 1, 29, 0, 0 ,0);
setTimeout(() => setTime(d), 0);
setInterval(() => setTime(d), 1000);