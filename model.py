import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
import pickle

def generateAI():
    data=pd.read_csv('data-ir.csv')

    X=data.iloc[:,:-1].values
    y=data.iloc[:,-1].values

    X=X.reshape(-1,1)
    X_train,X_test,y_train,y_test=train_test_split(X,y,test_size=0.2)

    ai=KNeighborsClassifier(n_neighbors=5)
    ai.fit(X_train,y_train)

    y_ai=ai.predict(X_test)
    accuracy_score(y_test,y_ai)
    pickle.dump(ai,open('ai.pkl','wb'))
    print('AI Model is Created')