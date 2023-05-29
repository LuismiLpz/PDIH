library(tuneR)
library(seewave)
library(audio)

nombre <- readWave('nombre.wav')
apellidos <- readWave('apellidos.wav')
length(nombre@left)
plot(extractWave(nombre, from = 1, to = 22644))

length(apellidos@left)
plot(extractWave(apellidos, from = 1, to = 25551))

str(nombre)
str(apellidos)

completo <- pastew(nombre, apellidos,output="Wave")
length(completo@left)
plot(extractWave(completo, from = 1, to = 48195))
str(completo)
writeWave(mezcla,file.path("completo.wav"))
mezcla <-bwfilter(completo ,f=22050, channel=1,n=1,from=10000/2,to=20000/2,bandpass=TRUE
                  ,listen=FALSE, output="Wave")

writeWave(mezcla,file.path("mezcla.wav"))

tmp <- readWave('completo.wav')
listen(tmp)
eco <- echo(tmp,f=22050,amp=c(0.8,0.4,0.2),delay=c(1,2,3),output="Wave")
listen(eco)
eco@left<-10000*eco@left
alreves <- revw(eco,output ="Wave")
listen(alreves)
writeWave(alreves,file.path("alreves.wav"))
