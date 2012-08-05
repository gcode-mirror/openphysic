#!/usr/bin/env python

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from pylab import figure, plot, show, grid, title, xlabel, ylabel, subplot, bar, np, xticks # plot
from matplotlib.finance import candlestick
from datetime import *

#def apply_SL(min):
  

print("Trade history")

"""
Provider Ticket
Broker Ticket
Type
Currency
Standard Lots
Date Open
Date Close
Price Open
Price Close
Highest Profit (Pips)
Worst Drawdown (Pips)
Interest ($)
Profit (Pips)
Profit ($)
"""

def conv_str_to_datetime(x):
  return(datetime.strptime(x, '%Y/%m/%d %H:%M:%S'))


#df = pd.read_csv('Trade_History_denganyouqianle_19850320_20120805.csv')
df = pd.read_csv('Trade_History_denganyouqianle_19850320_20120805.csv', converters={'Date Open': conv_str_to_datetime, 'Date Close': conv_str_to_datetime})

#df = pd.read_csv('Trade_History_denganyouqianle_19850320_20120805.csv', parse_dates=6, index_col=6)

#df = pd.read_csv('Trade_History_denganyouqianle_19850320_20120805.csv', parse_dates=[[5, 6]], index_col=0)
#df = pd.read_csv('Trade_History_denganyouqianle_19850320_20120805.csv', parse_dates=6, index_col=6)
# todo : il faudrait que les dates open et close soient parsees
#df['Duration']=df['Date Close']-df['Date Open']

#print(df.to_string(columns=['Currency', 'Date Open', 'Date Close', 'Profit (Pips)'],index=True))

#print(df.to_string())

df=df[df['Date Close']<datetime(2011,9,1)]
#df=df[df['Profit (Pips)']>100] # filter

#for row in df:
#	print row

df=df.sort(axis=0, ascending=False)
#df=df.sort(axis=0, ascending=True, columns='Date Close')
#df=df.sort(axis=0, ascending=False)
#df=df.sort(axis=0, ascending=False, column='Date Close')
#df=df.sort(axis=0, ascending=True)

#df=df[1:100]
#df=df[df['Date Open']>datetime(2012,1,1)] # tofix
#df=df[len(df)-100:len(df)] # derniers trades


#pd.set_printoptions(precision=2)

#df_resume = df.describe()
#for key in df_resume:
#  print("="*3+" {0} ".format(key) + "="*3)
#  print(df.describe()[key])
#  print("")


# invert trade
#df['Profit (Pips)'] = -df['Profit (Pips)']
#df['temp'] = df['Highest Profit (Pips)']
#df['Highest Profit (Pips)'] = -df['Worst Drawdown (Pips)']
#df['Worst Drawdown (Pips)'] = -df['temp']
#del df['temp']

#print(df)

#for row in df:

# optimistic : SL code and TP code
# pessimistic : TP code and SL code

# Apply TP Take Profit
#TP = 100
#b_hit_tp = df['Highest Profit (Pips)']>TP
#df['Profit (Pips)']=np.where(b_hit_tp,TP,df['Profit (Pips)'])

# Apply SL Stop Loss
#SL = 60
#b_hit_sl = df['Worst Drawdown (Pips)']<-SL
#df['Profit (Pips)']=np.where(b_hit_sl,-SL,df['Profit (Pips)'])

#ndf = df['Worst Drawdown (Pips)'] < -SL

#df['Profit (Pips)'] = -SL

#df[df['Worst Drawdown (Pips)'] < -SL]['Profit (Pips)'] = -SL

#df_hitSL=df[df['Worst Drawdown (Pips)']<-SL]
#df_hitSL['Profit (Pips)'] = -SL

#df=df.sort(axis=0, ascending=False, column='Date Close')

#print(df['Profit (Pips)'])

#print(df.head())

df_profit_pips_cum = df['Profit (Pips)'].cumsum()

#df_profit_pips.plot()

#df_profit_pips_cum.plot()
#plt.show()

#val = df.values
#print(val[0][0])

#print(df['Profit (Pips),Profit ($)'])

#print(df.values)

Date = range(1,len(df)+1)
#Date = range(len(df)+1,1,-1)
Open = np.zeros(len(df))
High = df['Highest Profit (Pips)'].values
Low = df['Worst Drawdown (Pips)'].values
Close = df['Profit (Pips)'].values
Volume = np.zeros(len(df))
DOCHLV = zip(Date, Open, Close, High, Low, Volume)

#print(DOCHLV)

fig = figure()
fig.subplots_adjust(bottom=0.1)
ax = fig.add_subplot(211)
# [(1, 0, 12.0, 12.0, -16.0, 0), ... (Date,Open,Close,High,Low,Volume)]
candlestick(ax, DOCHLV, width=0.6, colorup='g', colordown='r', alpha=1.0)

subplot(212)
df_profit_pips_cum.plot()

show()

#print(df['Duration'])