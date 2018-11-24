import pickle
# encoding=utf8  


with open('testInputA3.pkl', 'rb') as f:
    data = pickle.load(f)

print(data)
