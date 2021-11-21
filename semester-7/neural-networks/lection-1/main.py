import numpy as np
import pandas as pd

def divider():
    print("------------------------------")

def string_gender(female):
    return 'female' if female else 'male'

if __name__ == "__main__":
    np.set_printoptions(precision=2)

    data = pd.read_csv('beauty.csv', sep=';')
    print(type(data))
    print(data.head())
    #  print(data.shape())
    print(data.info())
    print(data.describe())
    divider()

    print(data['exper'].head())
    print(data.loc[0:5, ['wage', 'female']])
    print(data.iloc[:, 2:4])
    divider()

    print(data[data["female"]==1]["wage"].mean())
    print(data[data["female"]==0]["wage"].mean())
    divider()

    print(data[(data["female"] == 0) & (data["married"] == 1)]["wage"].median())
    print(data[(data["female"] == 0) & (data["married"] == 0)]["wage"].median())
    divider()

    for look, sub_df in data.groupby("looks"):
        print(look)
        print(sub_df["female"].mean())
    divider()

    print(data.groupby("looks")[['wage', 'exper']].agg(np.median))
    divider()

    print(pd.crosstab(data['female'], data['married']))
    divider()
    print(pd.crosstab(data['female'], data['looks']))
    divider()

    print(data['wage'].quantile(.75).astype('int64'))
    data['is_rich'] = (data['wage'] > data['wage'].quantile(.75)).astype('int64')

    print(data.head())

    data['rubbish'] = .56 * data['wage'] + 0.32 * data['exper']

    d = {1 : 'union', 0: 'non-union'}

    print(data['union'].map(d).head())
    print(data['female'].apply(lambda x : string_gender(x)).head())

