// Simplemente para un efecto suave al hacer clic en los enlaces de navegación
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function(e) {
        e.preventDefault();
        document.querySelector(this.getAttribute('href')).scrollIntoView({
            behavior: 'smooth'
        });
    });
});

var n_estrellas = 500;
var cv, cx, estrellas = [];
var vel_max = 10;

function prepararEstrella(index) {
    estrellas[index] = {
        'color': 'rgb(' +
            (Math.random() * 255) + ',' +
            (Math.random() * 255) + ',' +
            (Math.random() * 255) + ')',
        'vel_x': (Math.random() * vel_max * 2) - vel_max + 1,
        'vel_y': (Math.random() * vel_max * 2) - vel_max + 1,
        'x': Math.random() * cv.width, // Posición inicial aleatoria
        'y': Math.random() * cv.height
    };
}

function pintar() {
    // Limpiar el área con un cuadro negro
    cx.fillStyle = '#000';
    cx.fillRect(0, 0, cv.width, cv.height);

    for (var i = 0; i < n_estrellas; i++) {
        var e = estrellas[i];
        cx.fillStyle = e.color;
        if (e.x > cv.width || e.y > cv.height || e.x < 0 || e.y < 0) {
            prepararEstrella(i); // Reposicionar estrella si sale del canvas
        }
        e.x += e.vel_x; // Actualizar posición en X
        e.y += e.vel_y; // Actualizar posición en Y
        cx.fillRect(e.x, e.y, 2, 2); // Dibujar estrella
    }

    requestAnimationFrame(pintar); // Mejor rendimiento que setTimeout
}

function ajustarCanvas() {
    cv.width = window.innerWidth; // Ancho dinámico
    cv.height = window.innerHeight; // Alto dinámico
}

window.onload = function () {
    cv = document.getElementById('lienzoo');
    cx = cv.getContext('2d');

    ajustarCanvas(); // Ajustar el canvas al cargar

    // Redimensionar el canvas cuando cambie el tamaño de la ventana
    window.addEventListener('resize', ajustarCanvas);

    // Inicializar las estrellas
    for (var i = 0; i < n_estrellas; i++) {
        prepararEstrella(i);
    }

    // Comenzar la animación
    pintar();
};

