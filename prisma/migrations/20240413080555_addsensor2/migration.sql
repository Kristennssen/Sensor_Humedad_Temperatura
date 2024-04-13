-- CreateTable
CREATE TABLE "sensor2" (
    "id" SERIAL NOT NULL,
    "nombre" TEXT NOT NULL,
    "correo" TEXT NOT NULL,
    "carne" TEXT NOT NULL,
    "latitud" DECIMAL(65,30) NOT NULL,
    "Longitud" DECIMAL(65,30) NOT NULL,
    "temperatura" DECIMAL(65,30) NOT NULL,
    "humedad" DECIMAL(65,30) NOT NULL,
    "device" TEXT NOT NULL,
    "ip" TEXT NOT NULL,
    "date" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT "sensor2_pkey" PRIMARY KEY ("id")
);
