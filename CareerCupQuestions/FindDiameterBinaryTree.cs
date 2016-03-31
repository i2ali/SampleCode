using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CareerCupQuestions
{

    public class Node
    {
        public Node right;
        public Node left;
        public int data;

        public Node() {
            right = null;
            left = null;
            data = 0;
        }
        public Node(int val)
        {
            right = null;
            left = null;
            data = val;
        }

    } // Node

    public class DiameterData
    {
        public int diameter;
        public int height;

        public DiameterData() {
            diameter = 0;
            height = 0;
        }
    }

    class BinaryTree
    {
        public Node TreeBuilder()
        {
            int i = 0;
            Node root = new Node(i);
            root.left = new Node(++i);
            root.right = new Node(++i);

            root.left.left = new Node(++i);
            root.left.right = new Node(++i);

            root.right.left = new Node(++i);
            root.right.right = new Node(++i);

            root.right.left.right = new Node(++i);
            root.right.left.right.left = new Node(++i);


            return root;
        }

        // in order traversal
        public void printTree(Node node)
        {
            if (node != null)
            {
                printTree(node.left);
                Console.WriteLine(node.data);        
                printTree(node.right);
            }
        }

        public int FindDiameterBinaryTree_General(Node node) 
        {
           if (node == null)
                return 0;
        
            int lHeight = GetHeight(node.left);
            int rHeight = GetHeight(node.right);

            int lDiameter = FindDiameterBinaryTree_General(node.left);
            int rDiameter = FindDiameterBinaryTree_General(node.right);

            return ( Math.Max(lHeight + rHeight + 1, Math.Max(lDiameter, rDiameter)) );           
        
        }

        public DiameterData FindDiameterBinaryTree(Node node)
        {
            DiameterData d = new DiameterData();                          
            
            if (node == null)
                return d;
           
            DiameterData leftresult = FindDiameterBinaryTree(node.left);
            DiameterData rightresult = FindDiameterBinaryTree(node.right);

            d.height = Math.Max ( leftresult.height, rightresult.height ) + 1;
            
            int rootdiameter = leftresult.height + rightresult.height + 1;

            d.diameter = Math.Max ( rootdiameter, Math.Max ( leftresult.diameter, rightresult.diameter ) );

            return d;
        }

        public int FindDiameterBinaryTree_Optimal(Node node)
        {
            DiameterData d = FindDiameterBinaryTree(node);
            return d.diameter;
        }


        public int GetHeight(Node node)
        {
            if (node == null)
                return 0;

            return 1 + Math.Max(GetHeight(node.left), GetHeight(node.right));
       
        }
    
    }

    

}
