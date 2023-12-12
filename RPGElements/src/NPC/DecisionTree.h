#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class DecisionTreeNode
{
public:
   virtual ~DecisionTreeNode() {}
   virtual const std::string& MakeDecision(const std::string& context) = 0;
};

class Decision : public DecisionTreeNode
{
public:
   Decision(const std::string& action) : m_action(action) {}

   const std::string& MakeDecision(const std::string& context) override { return m_action; }

private:
   std::string m_action;
};

class DecisionBranch : public DecisionTreeNode
{
public:
   DecisionBranch(const std::string& question) : m_question(question) {}

   void AddBranch(const std::string& choice, std::shared_ptr<DecisionTreeNode> node) {
      m_branchMap[choice] = node;
   }

   bool AddBranchToNode(const std::string& targetQuestion, const std::string& choice, std::shared_ptr<DecisionTreeNode> node)
   {
      if (m_question == targetQuestion)
      {
         AddBranch(choice, node);
         return true;
      }
      for (auto& [key, branchNode] : m_branchMap)
      {
         auto decisionBranch = std::dynamic_pointer_cast<DecisionBranch>(branchNode);
         if (decisionBranch && decisionBranch->AddBranchToNode(targetQuestion, choice, node))
            return true;
      }
      return false;
   }

   bool RemoveBranch(const std::string& choice)
   {
      auto it = m_branchMap.find(choice);
      if (it != m_branchMap.end())
      {
         m_branchMap.erase(it);
         return true;
      }
      return false;
   }

   const std::string& MakeDecision(const std::string& context) override
   {
      auto it = m_branchMap.find(context);
      if (it != m_branchMap.end())
         return it->second->MakeDecision(context);

      static std::string defaultReturn = "None";
      return defaultReturn;
   }

private:
   std::string m_question;
   std::unordered_map<std::string, std::shared_ptr<DecisionTreeNode>> m_branchMap;
};

class DecisionTree
{
public:
   DecisionTree() {}

   std::shared_ptr<DecisionTreeNode> CreateRoot(const std::string& question)
   {
      auto root = std::make_shared<DecisionBranch>(question);
      if (root)
         m_root = root;
      return m_root;
   }

   bool AddBranch(const std::string& targetQuestion, const std::string& choice, std::shared_ptr<DecisionTreeNode> node)
   {
      auto rootBranch = std::dynamic_pointer_cast<DecisionBranch>(m_root);
      if (rootBranch)
         return rootBranch->AddBranchToNode(targetQuestion, choice, node);
      return false;
   }

   bool RemoveBranch(const std::string& choice) {
      auto rootBranch = std::dynamic_pointer_cast<DecisionBranch>(m_root);
      if (rootBranch)
         return rootBranch->RemoveBranch(choice);
      return false;
   }

   const std::string& MakeDecision(const std::string& context)
   {
      if (m_root)
         return m_root->MakeDecision(context);
      static std::string defaultReturn = "None";
      return defaultReturn;
   }

   void SetRoot(const std::shared_ptr<DecisionTreeNode>& rootNode) { m_root = rootNode; }

private:
   std::shared_ptr<DecisionTreeNode> m_root;
};
