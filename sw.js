self.addEventListener('push', function(event) {
    const options = {
        body: event.data ? event.data.text() : 'Notificación sin contenido',
        icon: 'imagenes/campanita.png',
    };

    event.waitUntil(
        self.registration.showNotification('Título de la Notificación', options)
    );
});
