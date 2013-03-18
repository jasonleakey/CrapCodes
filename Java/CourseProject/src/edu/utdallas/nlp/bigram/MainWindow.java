package edu.utdallas.nlp.bigram;

import java.awt.Component;
import java.awt.EventQueue;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultComboBoxModel;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.ListCellRenderer;
import javax.swing.UIManager;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;

public class MainWindow
{

    private JFrame frmNlpHomework;

    private JPanel panel;

    private JScrollPane scrollPane;

    private JTable table;

    private JComboBox<String> comboBox;

    private final static String[] SENTENCES = {
            "The company chairman said he will increase the profit next year .",
            "The president said he believes the last year profit were good ." };

    private DefaultComboBoxModel<String> comboModel = new DefaultComboBoxModel<>(
            SENTENCES);

    private BigramModel biModel;

    private JTable countTable;

    private RowHeaderModel<String> rowHeaderModel;

    /**
     * Launch the application.
     */
    public static void main(String[] args)
    {
        EventQueue.invokeLater(new Runnable()
        {
            public void run()
            {
                try
                {
                    MainWindow window = new MainWindow();
                    window.frmNlpHomework.setVisible(true);
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        });
    }

    /**
     * Create the application.
     */
    public MainWindow()
    {
        // train samples.
        biModel = new BigramModel();
        biModel.train();

        initialize();
    }

    /**
     * Initialize the contents of the frame.
     */
    private void initialize()
    {
        frmNlpHomework = new JFrame();
        frmNlpHomework.setBounds(100, 100, 595, 353);
        frmNlpHomework.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frmNlpHomework.setTitle("NLP Homework 2 - Yetian Huang");
        frmNlpHomework.getContentPane()
                .setLayout(
                        new BoxLayout(frmNlpHomework.getContentPane(),
                                BoxLayout.X_AXIS));

        Box verticalBox = Box.createVerticalBox();
        frmNlpHomework.getContentPane().add(verticalBox);

        Box horizontalBox = Box.createHorizontalBox();
        verticalBox.add(horizontalBox);

        JLabel lblNewLabel = new JLabel("Input sentence: ");
        horizontalBox.add(lblNewLabel);

        JButton btnNewButton = new JButton("Apply");
        btnNewButton.addMouseListener(new MouseAdapter()
        {
            @Override
            public void mouseClicked(MouseEvent e)
            {
                String inputSentence = comboModel.getElementAt(comboBox
                        .getSelectedIndex());
                if (null == inputSentence || inputSentence.isEmpty())
                {
                    // Do nothing
                    return;
                }

                updateTable(inputSentence);
            }
        });

        comboBox = new JComboBox<String>();
        comboBox.setModel(comboModel);
        horizontalBox.add(comboBox);
        horizontalBox.add(btnNewButton);

        panel = new JPanel();
        verticalBox.add(panel);
        panel.setLayout(new GridLayout(1, 2, 5, 5));

        scrollPane = new JScrollPane();
        panel.add(scrollPane);

        rowHeaderModel = new RowHeaderModel<>();
        JList<String> rowHeader = new JList<String>(rowHeaderModel);
        rowHeader.setFixedCellWidth(50);
        
        table = new JTable();
        table.setCellSelectionEnabled(true);
        scrollPane.setRowHeaderView(rowHeader);
        table.setModel(new DefaultTableModel(new Object[][] {
                { null, null, null }, { null, null, null },
                { null, null, null }, }, new String[] { "",
                "", "" }));
        rowHeader.setFixedCellHeight(table.getRowHeight()
                + table.getRowMargin());
        // + table.getIntercellSpacing().height);
        rowHeader.setCellRenderer(new RowHeaderRenderer(table));
        
        countTable = new JTable();
        scrollPane.setViewportView(countTable);
    }

    private void updateTable(String input)
    {
        Object[][] biCountTable = biModel.count(input);
        // extract column and row headers
        String[] header = (String[]) biCountTable[0];
        // display Row Header
        rowHeaderModel = new RowHeaderModel<String>(header);

        // display Column Header
        Integer[][] data = new Integer[biCountTable.length - 1][biCountTable[0].length];
        System.arraycopy(biCountTable, 1, data, 0, biCountTable.length - 1);
        table.setModel(new DefaultTableModel(data, header));

        // table.setModel(biCountTable, new String[] )
    }

    private class RowHeaderModel<E> extends DefaultListModel<E>
    {
        private static final long serialVersionUID = -2348686704371851896L;

        public RowHeaderModel()
        {
            super();
        }
        
        public RowHeaderModel(E[] list)
        {
            for (E elem : list)
            {
                super.addElement(elem);
            }
        }

        public void setElements(E[] list)
        {
            for (E elem : list)
            {
                super.addElement(elem);
            }
        }
    }

    private class RowHeaderRenderer extends JLabel implements
            ListCellRenderer<Object>
    {
        private static final long serialVersionUID = -30979490395364558L;

        RowHeaderRenderer(JTable table)
        {
            JTableHeader header = table.getTableHeader();
            setOpaque(true);
            setBorder(UIManager.getBorder("TableHeader.cellBorder"));
            setHorizontalAlignment(CENTER);
            setForeground(header.getForeground());
            setBackground(header.getBackground());
            setFont(header.getFont());
        }

        public Component getListCellRendererComponent(JList<?> list,
                Object value, int index, boolean isSelected,
                boolean cellHasFocus)
        {
            setText((value == null) ? "" : value.toString());
            return this;
        }
    }
}
