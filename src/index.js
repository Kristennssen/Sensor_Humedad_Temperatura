const express = require('express'); 
const { PrismaClient } = require('@prisma/client');
require('dotenv').config();
const prisma = new PrismaClient();
const app = express();
const PORT = process.env.PORT;
app.use(express.json());

app.get('/users', async (req, res)=>{
    try{
        const users = await prisma.usuarios.findMany();
        res.json(users);

    }catch(error){
        console.error('error buscando usuarios:', error);
        res.status(500).send('error del serivor')
    }
});

app.post('/users', async (req, res)=>{
    const users = await prisma.usuarios.create({
        data: req.body
    })
    res.json(users);
});

app.post('/sensor2', async (req, res)=>{
    const sensor2 = await prisma.sensor2.create({
        data: req.body
    }) 
    res.json(sensor2);
});

app.get('/sensor2', async (req, res)=>{
    const sensor2 = await prisma.sensor2.findMany();
    res.json(sensor2);
})

app.listen(PORT, () => {
console.log(`Server is running on port ${PORT}`);
});