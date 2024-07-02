
/*
    ======= El juego de la vida ====
    Se juega en cuadriculas y existen celulas vivas o muertas.

    Al inicio se representa una disposición inicial o semilla y comienza a iterar en generaciones (son series de tiempo, frame por frame)

    REGLAS
    1 Para que una celula siga viva, tener 2 o 3 vecinas, si tiene mas muere de superpoblación, si tiene menos muere de soledad.
    2. Si una celula esta muerta y tiene 3 vecinas vivas revive

    Definición de celula
    . = Muerta (Representada por un punto)
    O = VIVA (Representada por una letra O)

    Se observa la evolución de estas reglas a través del tiempo

    Simula una maquina universal de turing, demuestra que cualquier calculo que pueda ser descrito algoritmicamente puede ser procesado por cualquier máquina,
    es la base de la matematica
*/
const runConway = () => {

    const ANCHO = 10
    const ALTO = 10
    
    let grilla = crearGrilla(ANCHO, ALTO)
    grilla[1][2] = 1;
    grilla[2][3] = 1;
    grilla[3][1] = 1;
    grilla[3][2] = 1;
    grilla[3][3] = 1;

    let generacion = 0

    setInterval(() => {
        imprimirGrilla(generacion, grilla, ANCHO, ALTO)
        grilla = nuevaGeneracion(grilla, ANCHO, ALTO)
        generacion ++;
    }, 500)
    
}


const crearGrilla = (ancho, alto) => {
    let grilla = new Array(alto)

    for (let i = 0; i < alto; i++){
        grilla[i] = new Array(ancho).fill(0)
    }

    return grilla
}

const imprimirGrilla = (generacion, grilla, ancho, alto) => {
    console.clear()
    console.log(`Generación nº: ${generacion}`)
    for (let i = 0; i < alto; i++){
        let fila = "";
        for (let j = 0; j < ancho; j++) {
            fila += grilla[i][j] === 1 ? 'O ' : '. ';
        }
        console.log(fila);
    }
}

const nuevaGeneracion = (grilla, ancho, alto) => {

    let nuevaGrilla = crearGrilla(ancho, alto)

    for (let i = 0; i < alto; i++) {
        for (let j = 0; j < ancho; j++) {

            let vecinosVivos = 0

            // Explorando alrededor de la celula seleccionada para encontrar las vivas
            for (let x = -1; x <= 1; x++) {
                for (let y = -1; y <= 1; y++) {
                    if (x === 0 && y === 0) continue;
                    let ni = i + x; // Columna a revisar
                    let nj = j + y; // Fila a revisar

                    /*
                        Reglas de negocio
                        ni >= 0 : Siempre la columna debe ser mayor a 0 si es menor quiere decir que esta fuera del arreglo
                        ni < height : Siempre la columna debe ser menor al tamaño si es mayor quiere decir que esta fuera del arreglo
                        nj >= 0 : Siempre la fila debe ser mayor a 0 si es menor quiere decir que esta fuera del arreglo
                        nj < width : Siempre la fila debe ser menor al tamaño si es mayor quiere decir que esta fuera del arreglo
                    */
                    if (ni >= 0 && ni < alto && nj >= 0 && nj < ancho) {
                        vecinosVivos += grilla[ni][nj]; // Como la celula viva es 1 se va acumulando
                    }
                }
            }


            const estaViva = grilla[i][j] === 1

            if(estaViva){
                // 1 Para que una celula siga viva, tener 2 o 3 vecinas, si tiene mas muere de superpoblación, si tiene menos muere de soledad.
                if(vecinosVivos < 2 || vecinosVivos > 3){
                    nuevaGrilla[i][j] = 0 // Muere
                }else{
                    nuevaGrilla[i][j] = 1
                }
            }else{
                // 2. Si una celula esta muerta y tiene 3 vecinas vivas revive
                if(vecinosVivos === 3){
                    nuevaGrilla[i][j] = 1
                }else{
                    nuevaGrilla[i][j] = 0 // Muere
                }
            }
        }
    }

    return nuevaGrilla
}

runConway()