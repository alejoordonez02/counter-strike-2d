#!/bin/bash

# Configuración
TILESHEET="spritesheet.png"  # Cambia por tu ruta si es necesario
TILE_SIZE=32
OUTPUT_PREFIX="tile"

# Verificar que existe el tilesheet
if [ ! -f "$TILESHEET" ]; then
    echo "Error: No se encuentra $TILESHEET"
    echo "Coloca el archivo en este directorio o edita el script con la ruta correcta"
    exit 1
fi

# Obtener dimensiones (forma compatible)
width=$(identify -format "%w" "$TILESHEET")
height=$(identify -format "%h" "$TILESHEET")

# Calcular columnas y filas
cols=$((width / TILE_SIZE))
rows=$((height / TILE_SIZE))

# Crear los tiles
echo "Dividiendo $TILESHEET ($width x $height) en $cols x $rows tiles..."
convert "$TILESHEET" -crop ${TILE_SIZE}x${TILE_SIZE} +repage +adjoin "${OUTPUT_PREFIX}_%02d.png"

echo "¡Listo! Se crearon $((cols * rows)) tiles."