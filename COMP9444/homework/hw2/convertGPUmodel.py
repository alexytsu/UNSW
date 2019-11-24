import torch
from part3 import Network, PreProcessing
net = Network().to("cpu")
print(f'Loading model..')
model_name = input("Model Name: ")
net.load_state_dict(torch.load(f'{model_name}', map_location=torch.device("cuda:0")))
torch.save(net.state_dict(), f'./{model_name}')
print("Model saved")