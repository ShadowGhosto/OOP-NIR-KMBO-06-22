library("lmtest")
library("GGally") 
library("car")
library("foreign")
library("dplyr")
library("sandwich") 
library("rlms")
library("rstatix")
library("haven")
library("devtools")

data <- read.csv("C:/Users/Иван/Desktop/уник/R/r12i_os26b.csv",sep=",", dec = ".", header=TRUE)
glimpse(data)
data = select(data, hh5, h_age, h_marst, h_diplom, status, hj13.2, hj6.2)
data = na.omit(data)
glimpse(data)

##Обновленная база данных для нормализованных значений
data2 = select(data) 
glimpse(data)


#Пол
data2["sex"] = 0
data2$sex[which(data$hh5 == 1)] <- 1

#Возраст
age = data$h_age
data2["age"] = (age - mean(age)) / sqrt(var(age))

##Семейное положение:

#Состоит ли в зарегестрированном браке?
data2$wed1 = 0
data2$wed1[which(data$h_marst==2)] <- 1
data2$wed1[which(data$h_marst==6)] <- 1

#Разведён или вдовец?
data2$wed2 = 0
data2$wed2[which(data$h_marst==4)] <- 1
data2$wed2[which(data$h_marst==5)] <- 1

#Никогда не состоял в браке?
data2$wed3 = 0
data2$wed3[which(data$h_marst==1)] <- 1

#Проверим, что отсутствует линейная зависимость между семейными положениями
vif(lm(data$hj13.2 ~ data2$wed1 + data2$wed2 + data2$wed3)) 

#Наличие высшего образования
data2$higher_educ = 0
data2$higher_educ[which(data$h_diplom==6)] <- 1

#Живёт ли в городе  
data2$city_status = 0
data2$city_status[which(data$status==1)] <- 1
data2$city_status[which(data$status==2)] <- 1

#Нормализованное среднее число рабочих часов в неделю
working_hours = data$hj6.2
data2$working_hours = (working_hours - mean(working_hours)) / sqrt(var(working_hours))

#Нормализованная средняя зарплата
salary = data$hj13.2
data2$salary = (salary - mean(salary)) / sqrt(var(salary))

#####Постройте линейную регрессию зарплаты на все параметры, которые Вы выделили из данных мониторинга. Не забудьте оценить коэффициент вздутия дисперсии VIF.

model1 = lm(data = data2, salary ~ sex + age + wed1 + wed2 + wed3 + higher_educ + city_status + working_hours)
vif(model1)
summary(model1)
#R^2 ~ 0.01819, плохая p-статистика и vif, исключаю wed1


model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + higher_educ + city_status + working_hours)
vif(model1)
summary(model1)
#R^2 ~ 0.01784, плохая p-статистика, исключаю  higher_educ, увеличевается R^2.

model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + working_hours)
vif(model1)
summary(model1)
#R^2 ~ 0.01811, плохая p-статистика.

#####Поэкспериментируйте с функциями вещественных параметров: используйте логарифм и степени (хотя бы от 0.1 до 2 с шагом 0.1).

#Логарифмы и степени имеет смысл вводить только для параметров age и working_hours, так как остальные принимают только значения 0 или 1.
#с логарифмами:

model1 = lm( salary ~ sex + age + wed2 + wed3 + city_status + working_hours + I(log(Mod(working_hours))) + I(log(Mod(age))), data=data2)
vif(model1)
summary(model1) 
#R^2 ~ 0.01875
#плохая p-статистика и vif для working_hours и I(log(Mod(working_hours))), исключаю working_hours


model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(log(Mod(working_hours)))+ I(log(Mod(age))))
vif(model1)
summary(model1) 
#R^2 ~ 0.01821
#чуть улучшилась p-статистика и хороший vif. 


#Со степенями:
current_pow=0.1
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 
#R^2 ~ 0.01821
#Хорошие значения vif


current_pow = 0.2
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 
#R^2 ~  0.01821
#Хорошие значения vif


current_pow = 0.3
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 
#R^2 ~  0.0182
#Хорошие значения vif


current_pow = 0.4
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 
#R^2 ~  0.01818
#Хорошие значения vif


current_pow = 0.5
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 
#R^2 ~  0.01816
#Хорошие значения vif


current_pow = 0.6
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 
#R^2 ~  0.01813
#Хорошие значения vif


current_pow = 0.7
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 
#R^2 ~  0.0181
#Хорошие значения vif


current_pow = 0.8
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 
#R^2 ~  0.01807
#Хорошие значения vif


current_pow = 0.9
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1)
#R^2 ~  0.01803
#Хорошие значения vif


#Для степени 1 результат мы уже имеем


current_pow = 1.1
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1)
#R^2 ~  0.01797
#Хорошие значения vif


current_pow = 1.2
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1)
#R^2 ~  0.01794
#Хорошие значения vif


current_pow = 1.3
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1)
#R^2 ~  0.01791
#Хорошие значения vif


current_pow = 1.4
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1)
#R^2 ~  0.01789
#Хорошие значения vif


current_pow = 1.5
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1)
#R^2 ~  0.01787
#Далее в период с current_pow = 1.5 до current_pow = 2.0: чуть уменьшгается R^2 везде хорошие значения VIF и везде плохая p-статистика.



#####Выделите наилучшие модели из построенных: по значимости параметров, включённых в зависимости , и по объяснённому с помощью построенных зависимостей разбросу adjusted R2 - R2adj.

#Сравним лучшие модели: 
current_pow=0.1
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 
#Multiple R-squared:  0.02018,	Adjusted R-squared:  0.01821


current_pow = 0.2
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 
#Multiple R-squared:  0.02018,	Adjusted R-squared:  0.01821


current_pow = 0.3
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 
#Multiple R-squared:  0.02017,	Adjusted R-squared:  0.0182


#Разброс R2 - R2_adj везде одинаковый, а R^2 больше для степени 0.2


#Итого, среди моделей без линейной зависимости параметров с хорошими показателями p-статистики у регрессоров лучшей по R^2 оказалась модель для степени 0.1:  

current_pow=0.1
model1 = lm(data = data2, salary ~ sex + age + wed2 + wed3 + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model1)
summary(model1) 


#####Сделайте вывод о том, какие индивиды получают наибольшую зарплату.

#Учитывая лучшую модель больше всего зарабатывают молодые мужчины с высшим образованием, которые разведёны или не когда не были женаты, проживающие в городах,
#работающие большое число часов в неделю.



#####Оцените регрессии для подмножества индивидов: а) Не состоявшие в браке мужчины, с высшим образованием; б )городские жители, состоящие в браке, женщины.
current_pow = 0.1

#Не состоявшие в браке мужчины, с высшим образованием
data3 = subset(data2, wed3 == 1)
data3 = subset(data3, higher_educ == 1) 
data3 = subset(data3, sex == 1)

model1 = lm(data = data3, salary ~ age + city_status + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
#для добавления проверки vif требуется убрать значения NA по этому я удалил wed2 из списка регрессоров модели.
vif(model1) #хорошие значения vif 
summary(model1)
# R^2 ~ 0.07134
#Наибольшая зарплата у мужчин с высшим образованием старшего возраста, живущих в городе , не состоявшие в браке, работающих много.

#городские жители, состоящие в браке, женщины
data3 = subset(data2, sex == 0)
data3 = subset(data3, city_status == 1) 
data3 = subset(data3, wed1 == 1)
model1 = lm(data = data3, salary ~ age + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
#для добавления проверки vif требуется убрать значения NA по этому я удалил wed2 и wed3 из списка регрессоров модели.
vif(model1) #хорошие значения vif 
summary(model1)
# R^2 ~ 0.01782
#Наибольшая зарплата у работающих много, молодого возраста.