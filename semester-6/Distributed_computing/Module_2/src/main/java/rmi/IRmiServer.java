package rmi;

import entity.*;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface IRmiServer extends Remote {

    public Parameter selectParameter(int id) throws RemoteException;

    public List<Parameter> selectParameterList() throws RemoteException;

    public void insertParameter(Parameter parameter) throws RemoteException;

    public void updateParameter(int id, Parameter parameter) throws RemoteException;

    public void deleteParameter(int id) throws RemoteException;

    public Product selectProduct(int id) throws RemoteException;

    public List<Product> selectProductList() throws RemoteException;

    public void insertProduct(Product product) throws RemoteException;

    public void updateProduct(int id, Product product) throws RemoteException;

    public void deleteProduct(int id) throws RemoteException;

    public ParameterGroup selectParameterGroup(int id) throws RemoteException;

    public List<ParameterGroup> selectParameterGroupList() throws RemoteException;

    public void insertParameterGroup(ParameterGroup parameterGroup) throws RemoteException;

    public void updateParameterGroup(int id, ParameterGroup parameterGroup) throws RemoteException;

    public void deleteParameterGroup(int id) throws RemoteException;

    public ProductGroup selectProductGroup(int id) throws RemoteException;

    public List<ProductGroup> selectProductGroupList() throws RemoteException;

    public void insertProductGroup(ProductGroup productGroup) throws RemoteException;

    public void updateProductGroup(int id, ProductGroup productGroup) throws RemoteException;

    public void deleteProductGroup(int id) throws RemoteException;

    //Вывести перечень параметров для заданной группы продукции.
    public List<Parameter> task1(int groupId) throws RemoteException;

    //Вывести перечень продукции, не содержащий заданного параметра.
    public List<Product> task2(int parameterId) throws RemoteException;

    //Вывести информацию о продукции для заданной группы
    public List<Product> task3(int groupId) throws RemoteException;

    //Вывести информацию о продукции для заданной группы
    public List<ProductWithParameters> task4(int groupId) throws RemoteException;

    //Удалить из базы продукцию, содержащую заданные параметры.
    public void task5(List<Integer> parameters)  throws RemoteException;

    //Переместить группу параметров из одной группы товаров в другую.
    public void task6(long parameterGroupId, long fromGroupId, long toGroupId) throws RemoteException;
}

