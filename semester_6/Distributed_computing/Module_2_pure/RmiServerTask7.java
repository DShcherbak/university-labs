package rmi;

import entity.*;
import dao.DAOtask7;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.List;

public class RmiServerTask7 extends UnicastRemoteObject implements IRmiServer{
    public DAOtask7 dao;
    protected RmiServerTask7() throws RemoteException {
        super();
    }

    public Parameter selectParameter(int id) throws RemoteException {
        return dao.selectParameter(id);
    }

    public List<Parameter> selectParameterList() throws RemoteException {
        return dao.selectParameterList();
    }

    public void insertParameter(Parameter parameter) throws RemoteException {
        dao.insertParameter(parameter);
    }

    public void updateParameter(int id, Parameter parameter) throws RemoteException {
        dao.updateParameter(id, parameter);
    }

    public void deleteParameter(int id) throws RemoteException {
        dao.deleteParameter(id);
    }

    public Product selectProduct(int id) throws RemoteException {
        return dao.selectProduct(id);
    }

    public List<Product> selectProductList() throws RemoteException {
        return dao.selectProductList();
    }

    public void insertProduct(Product product) throws RemoteException {
        dao.insertProduct(product);
    }

    public void updateProduct(int id, Product product) throws RemoteException {
        dao.updateProduct(id, product);
    }

    public void deleteProduct(int id) throws RemoteException {
        dao.deleteProduct(id);
    }

    public ParameterGroup selectParameterGroup(int id) throws RemoteException {
        return dao.selectParameterGroup(id);
    }

    public List<ParameterGroup> selectParameterGroupList() throws RemoteException {
        return dao.selectParameterGroupList();
    }

    public void insertParameterGroup(ParameterGroup parameterGroup) throws RemoteException {
        dao.insertParameterGroup(parameterGroup);
    }

    public void updateParameterGroup(int id, ParameterGroup parameterGroup) throws RemoteException {
        dao.updateParameterGroup(id, parameterGroup);
    }

    public void deleteParameterGroup(int id) throws RemoteException {
        dao.deleteParameterGroup(id);
    }

    public ProductGroup selectProductGroup(int id) throws RemoteException {
        return dao.selectProductGroup(id);
    }

    public List<ProductGroup> selectProductGroupList() throws RemoteException {
        return dao.selectProductGroupList();
    }

    public void insertProductGroup(ProductGroup productGroup) throws RemoteException {
        dao.insertProductGroup(productGroup);
    }

    public void updateProductGroup(int id, ProductGroup productGroup) throws RemoteException {
        dao.updateProductGroup(id, productGroup);
    }

    public void deleteProductGroup(int id) throws RemoteException {
        dao.deleteProductGroup(id);
    }

    //Вывести перечень параметров для заданной группы продукции.
    public List<Parameter> task1(int groupId) throws RemoteException {
        return dao.task1(groupId);
    }

    //Вывести перечень продукции, не содержащий заданного параметра.
    public List<Product> task2(int parameterId) throws RemoteException {
        return dao.task2(parameterId);
    }

    //Вывести информацию о продукции для заданной группы
    public List<Product> task3(int groupId) throws RemoteException {
        return dao.task3(groupId);
    }

    //Вывести информацию о продукции для заданной группы
    public List<ProductWithParameters> task4(int groupId) throws RemoteException {
        return dao.task4(groupId);
    }

    //Удалить из базы продукцию, содержащую заданные параметры.
    public void task5(List<Integer> parameters) throws RemoteException {
        dao.task5(parameters);
    }

    //Переместить группу параметров из одной группы товаров в другую.
    public void task6(long parameterGroupId, long fromGroupId, long toGroupId) throws RemoteException {
        dao.task6(parameterGroupId,fromGroupId,toGroupId);
    }

    public static void main(String[] args) throws RemoteException {
        RmiServerTask7 server = new RmiServerTask7();
        server.dao = new DAOtask7();
        //server.dao.insertProduct(new Product("name", 1, "desc", Timestamp.valueOf("2020-04-21 00:00:00")));
        server.dao.task4(2);
        Registry r = LocateRegistry.createRegistry(1235);
        r.rebind("productDatabase", server);
    }
}

