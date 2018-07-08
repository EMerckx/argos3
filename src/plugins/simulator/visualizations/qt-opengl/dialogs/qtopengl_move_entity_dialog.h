/**
 * @file <argos3/plugins/simulator/visualizations/qt-opengl/dialogs/qtopengl_move_entity_dialog.h>
 *
 * @author Ewout Merckx - <ewoutmerckx.pro@gmail.com>
 */

#ifndef QTOPENGL_MOVE_ENTITY_DIALOG_H
#define QTOPENGL_MOVE_ENTITY_DIALOG_H

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_widget.h>

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>

namespace argos {

    class CQTOpenGLMoveEntityDialog : public QDialog {

        Q_OBJECT

        public:
            
            /**
             * Constructor
             * @param pc_parent_widget Pointer to the parent widget
             * @param pc_openglwidget Pointer to the OpenGL widget
             */
            CQTOpenGLMoveEntityDialog(QWidget* pc_parent_widget, CQTOpenGLWidget* pc_openglwidget);
            ~CQTOpenGLMoveEntityDialog() { }

        private:

            /**
             * Initialize the dialog box, add buttons, set the title
             */
            void Init();

        public slots:

            /**
             * Invoked when the user selects an other entity
             * Resets the error label
             */
            void EntitySelectionChanged();
            
            /**
             * Invoked when the user presses OK
             * Moves the entity in the arena, redraws the scene
             * Closes the dialog box afterwards
             */
            void Accept();

            /**
             * Invoked when the user presses cancel
             * Closes the dialog box
             */
            void Reject();

        private:
            /* Drop down for all entity types */
            QComboBox* m_pcEntityIdComboBox;

            /* Position */
            QLineEdit* m_pcEnityPositionXLineEdit;
            QLineEdit* m_pcEnityPositionYLineEdit;
            QLineEdit* m_pcEnityPositionZLineEdit;

            /* Orientation */
            QLineEdit* m_pcEnityOrientationWLineEdit;
            QLineEdit* m_pcEnityOrientationXLineEdit;
            QLineEdit* m_pcEnityOrientationYLineEdit;
            QLineEdit* m_pcEnityOrientationZLineEdit;

            /* Red error label */
            QLabel* m_pcErrorLabel;

            /* Widget for drawing */
            CQTOpenGLWidget* m_pcOpenGLWidget;
    };
}

#endif