using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CareerCupQuestions
{
    class Program
    {
        static void Main(string[] args)
        {
            // Test DiamaterofBinaryTree

            BinaryTree b = new BinaryTree();

            Node root = b.TreeBuilder();

            b.printTree(root);

            Console.WriteLine("Diameter of Binary Tree: {0}", b.FindDiameterBinaryTree_General(root));

            Console.WriteLine("Diameter of Binary Tree: {0}", b.FindDiameterBinaryTree_Optimal(root));

        }
    }
}
