import pandas as pd
import matplotlib.pyplot as mtp
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler

df = pd.read_csv('marketing_campaign.csv', sep='\t')

features = ['Income', 'MntWines', 'MntFruits', 'MntMeatProducts', 'MntFishProducts', 'MntSweetProducts', 'MntGoldProds', 'NumWebPurchases', 'NumCatalogPurchases', 'NumStorePurchases']
df_model = df[features].copy()

df_model = df_model.fillna(df_model.median())

scaler = StandardScaler()
x_scaled = scaler.fit_transform(df_model)

wcss_list = []
for i in range(2, 11):
  kmeans = KMeans(n_clusters=i, init='k-means++', random_state=42)
  kmeans.fit(x_scaled)
  wcss_list.append(kmeans.inertia_)

mtp.plot(range(2, 11), wcss_list, marker='o')
mtp.title('The Elbow Method Graph')
mtp.xlabel('Number of clusters (k)')
mtp.ylabel('wcss_list')
mtp.show()

kmeans = KMeans(n_clusters=4, init='k-means++', random_state=42)
y_predict = kmeans.fit_predict(x_scaled)
df['Cluster'] = y_predict

colors = ['blue', 'green', 'red', 'black']
labels = ['Cluster 1', 'Cluster 2', 'Cluster 3', 'Cluster 4']

for i in range(4):
  mtp.scatter(
      df_model['Income'][y_predict == i],
      df_model['MntWines'][y_predict == i],
      s=50, c=colors[i], label=labels[i]
  )
mtp.scatter(kmeans.cluster_centers_[:, 0], kmeans.cluster_centers_[:, 1], s=300, c='yellow', label='Centroid')
mtp.title('Customer Segments')
mtp.xlabel('Income')
mtp.ylabel('Wine Spending')
mtp.legend()
mtp.show()

print(df[['ID', 'Income', 'MntWines', 'MntMeatProducts', 'Cluster']])
