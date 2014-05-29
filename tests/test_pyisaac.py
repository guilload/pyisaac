import unittest

import pyisaac

from .fixtures import RESULTS


class PyisaacTestCase(unittest.TestCase):

    def test_pyisaac(self):
        """
        Test pyisaac with a seed and results provided by Bob Jenkins.
        """
        mytext = 'This is <i>not</i> the right mytext.'

        seed =  mytext + '\x00' * (1024 - len(mytext))
        pyisaac.seed(seed)
        
        self.assertListEqual([pyisaac.random() for _ in range(256 * 10)], RESULTS)