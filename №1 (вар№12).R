library("lmtest")
library("GGally")
library('tidyverse')

data=swiss
summary(data)
##Среднее значение элементов – Education, Examination, Fertility пакета swiss.
#data$Examination = 16.48936
#data$Agriculture = 50.65957
#data$Fertility = 70.14255
cat(mean(data$Examination))
cat(mean(data$Agriculture))
cat(mean(data$Fertility))

##Среднее квадратичное отклонение –Examination, Agriculture, Fertility пакета swiss.
#standard_deviation_Examination:  7.977883
#standard_deviation_Agriculture:  22.71122
#standard_deviation_Fertility:  12.4917
standard_deviation_Examination<-sqrt(sum((data$Examination - mean(data$Examination))^2/(length(data$Examination)-1)))
standard_deviation_Agriculture<-sqrt(sum((data$Agriculture - mean(data$Agriculture))^2/(length(data$Agriculture)-1)))
standard_deviation_Fertility<-sqrt(sum((data$Fertility - mean(data$Fertility))^2/(length(data$Fertility)-1)))

cat("standard_deviation_Examination: " , standard_deviation_Examination)

cat("standard_deviation_Agriculture: " ,standard_deviation_Agriculture)

cat("standard_deviation_Fertility: " , standard_deviation_Fertility)

##Дисперсия – Education, Examination, Fertility пакета swiss.
#data$Examination = 63.64662
#data$Agriculture = 515.7994
#data$Fertility = 156.0425
var(data$Examination)
var(data$Agriculture)
var(data$Fertility)

##Зависимости вида y= a + bx.
summary(lm(Examination~Fertility, data))
summary(lm(Examination~Agriculture, data))

cat(data$Examination_Fertility<-45.42 + (-0.412)*data$Fertility) 
cat(data$Examination_Agriculter<-28.70 + (-0.241)*data$Agriculture) 
#График зависимости data$Agriculture
ggplot(data=swiss, aes(x = data$Examination, y = data$Examination_Agriculter)) +
  
  geom_point(color= "red" , shape=25, fill= "blue" , size = 2.2, alpha = 0.5) +
  
  geom_smooth(method = 'loess',size=1.3, level=0.80)
#График зависимости data$Fertility
ggplot(data=swiss, aes(x = data$Examination, y = data$Examination_Fertility)) +
  
  geom_point(color= "red" , shape=25, fill="blue" , size =2.2, alpha= 0.5) +
  
  geom_smooth(method = 'loess' ,size=1.3, level=0.80)

##Коэффициент детерминации равен 64%, из этого следует, что 64% наших данных описывается нашей моделью. 
#Можем сделать вывод (R-squared = 64%), что модель относительно хороша: для такой
#зависимости (только две объясняющая переменная) коэффициент не мал, но для
#полного описания процесса нужно добавлять другие параметры.

##Значение p для переменной-предиктора Fertility равно 1.40e-05.(***) 
#Поскольку это значение меньше 0,05, оно имеет статистически значимую связь с переменной отклика в модели.
#Значение p для переменной-предиктора Agriculture равно 1.52e-06.(***) 
#Поскольку это значение меньше 0,05, оно имеет статистически значимую связь с переменной отклика в модели.

model = lm(Examination~Fertility+Agriculture, data )
model
summary(model)

## Из взаимосвязи вида y= a + bx можно сделать вывод, с ростом коэффициента Agriculture и Fertility уменьшается
# % призывников, получивших наивысшую оценку на армейском экзамене, следовательно взаимосвязи являются отрицательными.
cat(data$Examination_Fertility<-45.42 + (-0.412)*data$Fertility) 
cat(data$Examination_Agriculter<-28.70 + (-0.241)*data$Agriculture) 
#Вывод: обе взаимосвязи являются отрицательными.
