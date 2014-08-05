import unittest

import numpy as np

import pyisaac

from fixtures import RESULTS


class PyisaacTestCase(unittest.TestCase):

    mytext = 'This is <i>not</i> the right mytext.'
    mytext_seed =  mytext + '\x00' * (1024 - len(mytext))

    def setUp(self):
        self.seed()

    @classmethod
    def seed(cls):
        pyisaac.seed(cls.mytext_seed)

    def test_randuint32(self):
        for result in RESULTS:
            self.assertEqual(pyisaac.randuint32(), result)

    def test_random(self):
        for result in RESULTS:
            self.assertEqual(pyisaac.random(), result / (2.**32 - 1))

    def test_np_rand(self):
        m = len(RESULTS)
        array = pyisaac.np.rand(m)

        self.assertIsInstance(array, np.ndarray)
        self.assertEqual(array.shape, (m,))

        for i, result in zip(array, RESULTS):
            self.assertEqual(i, result / (2.**32 - 1))

        self.assertEqual(pyisaac.np.rand(1, 2).shape, (1, 2))
