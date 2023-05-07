library("lmtest")
library("GGally")
library("car")
library("dplyr")

data(Seatbelts)
data = na.omit(Seatbelts)
data <- as.data.frame(data)

##проверим возможность использования всех зявленных регрессоров в одной модели
model1=(lm(law~kms + PetrolPrice, data)) 
vif(model1)
summary(model1) #R^2 = 28%. относительно независимые регрессоры
model1=(lm(kms~law + PetrolPrice, data)) 
vif(model1) 
summary(model1) #R^2 = 27%. относительно независимые регрессоры
model1=(lm(PetrolPrice~law + kms, data)) 
vif(model1) 
summary(model1) #R^2 = 19%. относительно независимые регрессоры


##построим общую модель регрессии
model2 = lm(front~law + kms + PetrolPrice, data)
vif(model2) 
summary(model2)
#модель неплохая, но есть невзимосвязанная переменная kms (с отсутствием звездочек)
#Adjusted R-squared = 42%. По результатам зависимости front~law и front~PetrolPrice имеет три звездды.
#р-значение у kms большое.

##Получим коэф. R^2 для каждого отдельно
summary(lm(front~law, data))$r.squared  #R^2 равен 31%.
summary(lm(front~kms, data))$r.squared  #R^2 равен 12% Попробуем исключить.
summary(lm(front~PetrolPrice, data))$r.squared #R^2 равен 29%. 
summary(lm(front~law + PetrolPrice, data)) #Adjuster R-squared = 43%. Коэф. увеличился на 1% и улучшилась p-статистика, следовательно далее пользуемся этой моделью.



##Введем логарифмы 
#В модель нельзя ввести log регрессоров без замены значений равных 0 в таблице law на 0.001
data$law[data$law == 0] <- 0.001


#log регрессоров
model3=(lm(log(front)~ I(log(law)) + I(log(PetrolPrice)), data))
vif(model3)
summary(model3) #Лучшая модель log(front)~I(log(law), Adjusted R-squared: 0.4835
summary(lm(log(front)~I(log(law)), data))$r.squared #R^2 равен 39%.

model3 = lm(front ~ I(log(law)) + I(log(PetrolPrice)), data)     
vif(model3) 
summary(model3) #Лучшая модель log(front)~I(log(law), Adjusted R-squared:  0.4299
summary(lm(log(front)~I(log(law)), data))$r.squared #R^2 равен 39%.

model3 = lm(front ~ I(log(law)) + PetrolPrice, data)     
vif(model3) 
summary(model3) #Лучшая модель log(front)~I(log(law), Adjusted R-squared:  0.4309
summary(lm(log(front)~I(log(law)), data))$r.squared #R^2 равен 39%.

model3 = lm(front ~ law + I(log(PetrolPrice)), data)     
vif(model3) 
summary(model3) #Лучшая модель log(front)~I(log(law), Adjusted R-squared:  0.4299
summary(lm(log(front)~I(log(law)), data))$r.squared #R^2 равен 39%.




##Введем в модель всевозможные произведения пар регрессоров
model4 = lm(front ~ law + PetrolPrice + I(law^2) + I(PetrolPrice^2) + I(law*PetrolPrice), data) 
vif(model4) # есть линейная зависимость, уберём регрессоры с максимальным VIF
summary(model4)#Лучшая модель front~law, Adjusted R-squared:  0.428

model4 = lm(front ~ law + PetrolPrice + I(PetrolPrice^2) + I(law*PetrolPrice), data) 
vif(model4) # есть линейная зависимость, уберём регрессоры с максимальным VIF
summary(model4)#Лучшая модель front~law, Adjusted R-squared:  0.428

model4 = lm(front ~ law + PetrolPrice + I(PetrolPrice^2), data) 
vif(model4) # есть линейная зависимость, уберём регрессоры с максимальным VIF
summary(model4)#Лучшая модель front~law, Adjusted R-squared:  0.4278

model4 = lm(front ~ law + I(PetrolPrice^2), data) 
vif(model4) # линейной зависимости нет
summary(model4)#Лучшая модель front~law, Adjusted R-squared:  0.4306

#Наилучшей из всех будет следующая модель: 
model3_1 = (lm(log(front)~ I(log(law)) + I(log(PetrolPrice)), data))  # R^2 = 0.4835


##вывод: исходя из данного исследования самой лучшей моделью будет model3_1 со значением Adjusted R-squared:  0.4835, 
#самая сильная связь у log(front)~I(log(law) со значением Adjusted R-squared:  0.3911, но также существует хорошая зависимость front~law.