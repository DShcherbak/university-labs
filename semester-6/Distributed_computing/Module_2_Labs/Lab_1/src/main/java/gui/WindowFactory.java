package gui;

import connection.client.ClientProgram;
import gui.windows.*;
import objects.entity.Department;
import objects.entity.Employee;
import objects.entity.HumanResources;

import javax.swing.*;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class WindowFactory {
    public static Window GetWindow(GUI gui, GUI.GuiState state){
        return switch (state) {
            case StartScreen -> createStartWindow(gui);
            case ClientScreen -> createChooseClientWindow(gui);
            case DaoScreen -> createDaoWindow(gui);
            case DepartmentScreen -> createDepartmentScreen(gui);
            case EmployeeScreen -> createEmployeeScreen(gui);
            case AddDepartmentScreen -> createAddDepartmentScreen(gui);
            case AddEmployeeScreen -> createAddEmployeeScreen(gui);
        };
    }
    private static JFrame defaultJFrame(String title){
        JFrame f = new JFrame(title);
        GridBagLayout layout = new GridBagLayout();
        f.setLayout(null);
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension dimension = toolkit.getScreenSize();
        f.setBounds(dimension.width/2 - Window.width/2, dimension.height/2 - Window.height/2, Window.width,Window.height);
        f.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent windowEvent){
                System.exit(0);
            }
        });
        return f;
    }


    private static Window createStartWindow(GUI gui){
        JFrame startGameFrame = defaultJFrame("Start Screen");
        var window = new StartWindow(startGameFrame,  "Start Screen", gui);

        JButton xmlButton = new JButton("XML");
        xmlButton.setActionCommand("XML");
        window.addButton(xmlButton,"XML", 250,150,300, 50);

        JButton JdbcButton = new JButton("JDBC");
        JdbcButton.setActionCommand("JDBC");
        window.addButton(JdbcButton,"JDBC", 250,250,300, 50);

        JLabel label = new JLabel("",JLabel.CENTER );
        window.addLabel(label,"HEAD", 350,175,200, 50);

        return window;
    }

    private static Window createChooseClientWindow(GUI gui){
        JFrame startGameFrame = defaultJFrame("Choose connection.client-connection.server connection type");
        var window = new ClientChoosingWindow(startGameFrame,  "Start Screen", gui);

        JButton xmlButton = new JButton("RMI");
        xmlButton.setActionCommand("RMI");
        window.addButton(xmlButton,"RMI", 250,150,300, 50);

        JButton JdbcButton = new JButton("Socket");
        JdbcButton.setActionCommand("Socket");
        window.addButton(JdbcButton,"Socket", 250,250,300, 50);

        JLabel label = new JLabel("",JLabel.CENTER );
        window.addLabel(label,"HEAD", 350,175,200, 50);

        return window;
    }

    final static String ROOT = "Human Resources";
    private static Window createDaoWindow(GUI gui){
        JFrame startGameFrame = defaultJFrame("Human Resources");
        var window = new DaoWindow(startGameFrame,  "Start Screen", gui);

        JButton saveButton = new JButton("Save changes");
        saveButton.setActionCommand("SAVE");
        window.addButton(saveButton,"SAVE", 50,10,200, 40);

        JButton addDepButton = new JButton("Create a department");
        addDepButton.setActionCommand("ADD DEP");
        window.addButton(addDepButton,"ADD DEP", 300,10,200, 40);

        JButton addEmpButton = new JButton("Hire an employee");
        addEmpButton.setActionCommand("ADD EMP");
        window.addButton(addEmpButton,"ADD EMP", 550,10,200, 40);

        var humanResources = ClientProgram.getHumanResources();
        TreeModel model = createTreeModel(humanResources);
        JTree tree = new JTree(model);
        TreeSelectionModel selModel = new DefaultTreeSelectionModel();
        selModel.setSelectionMode(TreeSelectionModel.DISCONTIGUOUS_TREE_SELECTION);
        tree.setSelectionModel(selModel);
        tree.addTreeSelectionListener(new SelectionListener());
        JPanel contents = new JPanel(new GridLayout(1, 3));
        contents.add(new JScrollPane(tree));
        contents.setBounds(0,50, 800,600);
        contents.setSize(800,600);
        window.treePanel = contents;
        window.frame.add(contents);
        return window;
    }

    private static TreeModel createTreeModel(HumanResources humanResources) {
        DefaultMutableTreeNode root = new DefaultMutableTreeNode(ROOT);
        ArrayList<DefaultMutableTreeNode> nodes = new ArrayList<>();
        int i = 0;
        if(humanResources.departments != null){
            for (var department : humanResources.departments) {
                nodes.add(new DefaultMutableTreeNode(department));
                root.add(nodes.get(i));
                ArrayList<String> employees = humanResources.employees.get(department);
                for (int j = 0; j < employees.size(); j++)
                    nodes.get(i).add(new DefaultMutableTreeNode(employees.get(j), false));
                i++;
            }
        }
        return new DefaultTreeModel(root);
    }

    static class SelectionListener implements TreeSelectionListener {
        public void valueChanged(TreeSelectionEvent e)
        {
            String name = e.getPath().getLastPathComponent().toString();
            System.out.println(name);
            if(!name.equals(ROOT)){
                if(ClientProgram.getHumanResources().departments.contains(name)){
                    ClientProgram.setCurrentDepartment(name);
                    ClientProgram.gui.setCurrentState(GUI.GuiState.DepartmentScreen);
                } else {
                    ClientProgram.setCurrentEmployee(name);
                    ClientProgram.gui.setCurrentState(GUI.GuiState.EmployeeScreen);
                }
                ClientProgram.getGui().showEventDemo();
            }

        }
    }

    private static Window createDepartmentScreen(GUI gui){
        Department department = ClientProgram.getCurrentDepartment();
        JFrame startGameFrame = defaultJFrame("Department " + department.getName());
        var window = new DepartmentWindow(startGameFrame,  "Start Screen", gui);

        JLabel label = new JLabel("",JLabel.CENTER );
        window.addLabel(label,"HEAD", 350,10,200, 50);

        JButton backButton = new JButton("Back");
        backButton.setActionCommand("BACK");
        window.addButton(backButton,"BACK", 10,10,100, 25);

        JLabel nameLabel = new JLabel("Department name");
        window.addLabel(nameLabel,"NAME", 50,80,200, 50);
        JTextField nameField = new JTextField(department.getName());
        window.addField(nameField, "NAME", 250,80,200, 50);

        JLabel powerLabel = new JLabel("Influence");
        window.addLabel(powerLabel,"POWER", 50,130,200, 50);
        JTextField powerField = new JTextField(String.valueOf(department.getPower()));
        window.addField(powerField, "POWER", 250,130,200, 50);

        JLabel employeesLabel = new JLabel("Employees");
        window.addLabel(employeesLabel,"EMPLOYEES", 50,180,200, 50);

        ArrayList<String> list = (ArrayList<String>) department.getEmployees().stream().map(Employee::getFullName).collect(Collectors.toList());
        String[] data1 = list.toArray(new String[0]);
        JList<String> employeesList = new JList<>(data1);

        window.addList(employeesList, 250, 180, 200, 200);

        JButton updateButton = new JButton("Save changes");
        updateButton.setActionCommand("UPDATE");
        window.addButton(updateButton,"UPDATE", 50,480,200, 40);

        JButton deleteButton = new JButton("Dissolve department");
        deleteButton.setActionCommand("DELETE");
        window.addButton(deleteButton,"DELETE", 250,480,200, 40);
        return window;
    }

    private static Window createEmployeeScreen(GUI gui){
        Employee employee = ClientProgram.getCurrentEmployee();
        JFrame startGameFrame = defaultJFrame("Employee " + employee.getFullName());
        var window = new EmployeeWindow(startGameFrame,  "Start Screen", gui);

        JButton backButton = new JButton("Back");
        backButton.setActionCommand("BACK");
        window.addButton(backButton,"BACK", 10,10,100, 25);

        JLabel nameLabel = new JLabel("Name");
        window.addLabel(nameLabel,"NAME", 50,80,200, 50);
        JTextField nameField = new JTextField(employee.getName());
        window.addField(nameField, "NAME", 250,80,200, 50);

        JLabel surnameLabel = new JLabel("Surname");
        window.addLabel(surnameLabel,"SURNAME", 50,130,200, 50);
        JTextField surnameField = new JTextField(employee.getSurname());
        window.addField(surnameField, "SURNAME", 250,130,200, 50);

        JLabel powerLabel = new JLabel("Salary");
        window.addLabel(powerLabel,"SALARY", 50,180,200, 50);
        JTextField powerField = new JTextField(String.valueOf(employee.getSalary()));
        window.addField(powerField, "SALARY", 250,180,200, 50);

        JLabel positionLabel = new JLabel("Position");
        window.addLabel(positionLabel,"POSITION", 50,230,200, 50);
        JTextField positionField = new JTextField(employee.getPosition());
        window.addField(positionField, "POSITION", 250,230,200, 50);

        JLabel label = new JLabel("",JLabel.CENTER );
        window.addLabel(label,"HEAD", 350,10,200, 50);

        JLabel departmentLabel = new JLabel("Department");
        window.addLabel(departmentLabel,"DEPARTMENT", 50,280,200, 50);
        ArrayList<String> departmentsNames;
        ArrayList<Department> departments = new ArrayList<>();
        try {
           departments = (ArrayList<Department>) gui.Client().getDepartments();
        }catch (Exception ignored){}
        departmentsNames = (ArrayList<String>) departments.stream()
                .map(Department::getName).collect(Collectors.toList());
        long chosenIndex = 0;
        for(int i = 0; i < departments.size(); i++){
            if(departments.get(i).getId() == employee.getDepartmentId()){
                chosenIndex = i;
            }
        }
        String[] data1 = departmentsNames.toArray(new String[0]);
        JComboBox<String> department = new JComboBox<>(data1);
        department.setSelectedIndex((int) chosenIndex);
        window.addComboBox(department, 250, 280,200,50);

        JButton deleteButton = new JButton("Fire worker");
        deleteButton.setActionCommand("DELETE");
        window.addButton(deleteButton,"DELETE", 250,480,200, 40);

        JButton updateButton = new JButton("Save changes");
        updateButton.setActionCommand("UPDATE");
        window.addButton(updateButton,"UPDATE", 50,480,200, 40);



        return window;
    }

    private static Window createAddDepartmentScreen(GUI gui){
        JFrame startGameFrame = defaultJFrame("New Department");
        var window = new DepartmentWindow(startGameFrame,  "Start Screen", gui);

        JLabel label = new JLabel("",JLabel.CENTER );
        window.addLabel(label,"HEAD", 350,10,200, 50);

        JButton backButton = new JButton("Back");
        backButton.setActionCommand("BACK");
        window.addButton(backButton,"BACK", 10,10,100, 25);

        JLabel nameLabel = new JLabel("Department name");
        window.addLabel(nameLabel,"NAME", 50,80,200, 50);
        JTextField nameField = new JTextField("");
        window.addField(nameField, "NAME", 250,80,200, 50);

        JLabel powerLabel = new JLabel("Influence");
        window.addLabel(powerLabel,"POWER", 50,130,200, 50);
        JTextField powerField = new JTextField();
        window.addField(powerField, "POWER", 250,130,200, 50);


        JButton updateButton = new JButton("Create");
        updateButton.setActionCommand("ADD");
        window.addButton(updateButton,"ADD", 50,480,200, 40);
        return window;
    }

    private static Window createAddEmployeeScreen(GUI gui){
        JFrame startGameFrame = defaultJFrame("New Employee");
        var window = new EmployeeWindow(startGameFrame,  "Start Screen", gui);

        JButton backButton = new JButton("Back");
        backButton.setActionCommand("BACK");
        window.addButton(backButton,"BACK", 10,10,100, 25);

        JLabel label = new JLabel("",JLabel.CENTER );
        window.addLabel(label,"HEAD", 350,10,200, 50);

        JLabel nameLabel = new JLabel("Name");
        window.addLabel(nameLabel,"NAME", 50,80,200, 50);
        JTextField nameField = new JTextField();
        window.addField(nameField, "NAME", 250,80,200, 50);

        JLabel surnameLabel = new JLabel("Surname");
        window.addLabel(surnameLabel,"SURNAME", 50,130,200, 50);
        JTextField surnameField = new JTextField();
        window.addField(surnameField, "SURNAME", 250,130,200, 50);

        JLabel powerLabel = new JLabel("Salary");
        window.addLabel(powerLabel,"SALARY", 50,180,200, 50);
        JTextField powerField = new JTextField();
        window.addField(powerField, "SALARY", 250,180,200, 50);

        JLabel positionLabel = new JLabel("Position");
        window.addLabel(positionLabel,"POSITION", 50,230,200, 50);
        JTextField positionField = new JTextField();
        window.addField(positionField, "POSITION", 250,230,200, 50);

        JLabel departmentLabel = new JLabel("Department");
        window.addLabel(departmentLabel,"DEPARTMENT", 50,280,200, 50);
        ArrayList<Department> departments = new ArrayList<>();
        ArrayList<String> departmentsNames;
        try {
            departments = (ArrayList<Department>) gui.Client().getDepartments();
        }catch (Exception ignored){}
        departmentsNames = (ArrayList<String>) departments.stream()
                .map(Department::getName).collect(Collectors.toList());
        String[] data1 = departmentsNames.toArray(new String[0]);
        JComboBox<String> department = new JComboBox<>(data1);
        department.setSelectedIndex(0);
        window.addComboBox(department, 250, 280,200,50);

        JButton updateButton = new JButton("Create");
        updateButton.setActionCommand("ADD");
        window.addButton(updateButton,"ADD", 50,480,200, 40);
        return window;
    }

}
