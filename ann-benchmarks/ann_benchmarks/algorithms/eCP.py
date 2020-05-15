from __future__ import absolute_import
import eCP_wrapper as e
import numpy as np
from ann_benchmarks.algorithms.base import BaseANN

class eCP(BaseANN):
    def __init__(self, metric, L):
        self.L = L
        self.name = "eCP"
        
        if(metric == 'angular'):
            self.metric = 1
        else:
            self.metric = 0

    def fit(self, dataset):
        #dataset contains float32, we need to convert it to float64 for the eCP algorithm
        descriptors = dataset.astype(np.float64)

        self.index = e.eCP_Index(descriptors, self.L, self.metric)

    def query(self, q, k):
        #query point is float32, convert it to float64
        query = q.astype(np.float64)
        
        #returns a tuple of (index, distance)
        indices = e.query(self.index, query, k, self.b)[0]
        return indices
   
    def set_query_arguments(self, b):
        self.b = b

    def __str__(self):
        return 'eCP(L=%s, b=%s)' % (self.L, self.b)
