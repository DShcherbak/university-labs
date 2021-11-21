from __future__ import print_function
import numpy as np
import pandas as pd


def print(*args):
    __builtins__.print(*("%.2f" % a if (isinstance(a, float) and abs(a) >= 0.01) else a
                         for a in args))

def ask_question(str):
    print("------------------------------")
    print(str)

if __name__ == "__main__":

    np.set_printoptions(precision=2)
    pd.set_option("display.precision", 2)
    data = pd.read_csv('adult.data.csv', sep=',')
    #print(data.head())
    # print(data.info())
    # print(data['sex'].head())

    data['rich'] = data['salary'] == '>50K'

    ask_question('1. Скільки чоловіків та жінок представлено в цьому наборі даних?')
    print('Чоловіки: ', data[data['sex']=='Male'].shape[0])
    print('Жінки: ', data[data['sex']=='Female'].shape[0])

    ask_question('2. Який середній вік жінок?')
    print(data[data['sex']=='Female']['age'].mean())

    ask_question('3. Яка частка громадян Німеччини?')
    print(data[data['native-country'] == 'Germany'].shape[0]/data.shape[0])

    ask_question('4. Які середні значення та середньоквадратичні відхилення віку тих, хто отримує більше 50К в рік та менше або рівно 50К в рік?')
    print('Середній вік багатих: ', data[data['rich']]['age'].mean())
    print('Відхилення віку багатих: ', data[data['rich']]['age'].std())
    print('Середній вік бідних: ', data[data['rich']==False]['age'].mean())
    print('Відхилення віку бідних: ', data[data['rich']==False]['age'].std())

    ask_question('5. Чи правда, що люди, які отримують більше 50К, мають як мінімум вищу освіту?')
    print(data[(data['education'].isin(['Bachelors', 'Prof-school', 'Assoc-acdm', 'Assoc-voc', 'Masters', 'Doctorate'])) & (data['salary'] == '>50K')].shape[0] == 0)

    ask_question('6. Виведіть статистику віку для кожної раси і статі.')
    max_age_specific = 0
    for race, race_data in data.groupby('race'):
        print('................')
        print(race)
        if race == 'Amer-Indian-Eskimo':
            max_age_specific = race_data['age'].max()
        print(race_data.describe())


    ask_question('6.1.  Знайдіть максимальний вік чоловіків раси Amer-Indian-Eskimo.')
    print(max_age_specific)

    ask_question('7. Серед кого більша частка з високою зарплатнею (>50K): серед одружених або неодружених чоловіків (ознака marital-status)?')
    print(pd.crosstab(data[data['sex']=='Male']['marital-status'], data['rich']))

    data['is-married'] = (data['marital-status'].apply(lambda x : x[:7]=='Married'))

    married_man = data[(data['sex'] == 'Male') & (data['is-married'] == True)]
    unmarried_man = data[(data['sex'] == 'Male') & (data['is-married'] == False)]

    percent_of_rich_married_man = (married_man[married_man['rich']].shape[0]) / (married_man.shape[0])
    percent_of_rich_unmarried_man = (unmarried_man[unmarried_man['rich']].shape[0]) / (unmarried_man.shape[0])

    print('Відсоток заможних серед одружених чоловіків: ', percent_of_rich_married_man)
    print('Відсоток заможних серед холостих чоловіків: ', percent_of_rich_unmarried_man)

    ask_question('8. Яку максимальну кількість годин людина працює на тиждень')
    max_hours = data['hours-per-week'].max()
    print(max_hours)

    ask_question('8.1. Скільки людей працюють таку кількість годин?')
    hard_workers = data[data['hours-per-week'] == max_hours]
    print(hard_workers.shape[0])
    ask_question('8.2. Який серед них відсоток заробляють багато?')
    print((hard_workers[hard_workers['rich']].shape[0]) / (hard_workers.shape[0]))

    ask_question('9. Порахуйте середній час роботи тих, хто заробляє мало і багато для кожної країни.')
    for country, country_data in data.groupby('native-country'):
        print('Країна: ', country)
        print('Бідні в середньому працюють: ', country_data[country_data['rich']]['hours-per-week'].mean())
        print('Заможні в середньому працюють: ', country_data[country_data['rich']==False]['hours-per-week'].mean())





