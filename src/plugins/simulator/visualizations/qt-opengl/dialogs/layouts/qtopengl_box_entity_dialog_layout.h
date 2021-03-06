/**
 * @file <argos3/plugins/simulator/visualizations/qt-opengl/dialogs/layouts/qtopengl_box_entity_dialog_layout.h>
 *
 * @author Ewout Merckx - <ewoutmerckx.pro@gmail.com>
 */

#ifndef QTOPENGL_BOX_ENTITY_DIALOG_LAYOUT
#define QTOPENGL_BOX_ENTITY_DIALOG_LAYOUT

namespace argos {
    class CQTOpenGLBoxEntityDialogLayout;
}

#include <argos3/plugins/simulator/visualizations/qt-opengl/dialogs/layouts/qtopengl_embodied_entity_dialog_layout.h>

#include <QCheckBox>

namespace argos {

    class CQTOpenGLBoxEntityDialogLayout : public CQTOpenGLEmbodiedEntityDialogLayout {

        Q_OBJECT

        public:

            /**
             * Constructor.
             * @param pc_parent_widget The pointer to the parent widget
             */
            CQTOpenGLBoxEntityDialogLayout(QWidget* pc_parent_widget = 0);

            /**
             * Creates and returns the box entity using the specified values
             * @returns The entity using the specified values
             */
            virtual CEntity& GetEntity();

            /**
             * Getter for the size
             * @returns The vector containing the specified x,y,z values
             */
            inline CVector3 GetSize() const
            {
                return CVector3(
                    m_pcEnitySizeXLineEdit->text().toDouble(),
                    m_pcEnitySizeYLineEdit->text().toDouble(),
                    m_pcEnitySizeZLineEdit->text().toDouble()
                    );
            }

            /**
             * Getter for the movable input field
             * If the check-box is checked: true
             * If the check-box isn't checked: false
             * @returns The boolean for the movable attribute
             */
            inline bool IsMovable() const
            {
                return m_pcEnityIsMovableCheckBox->isChecked();
            }

            /**
             * Getter for the mass
             * @returns The real number containing the specified mass value
             */
            inline Real GetMass() const
            {
                return m_pcEnityMassLineEdit->text().toDouble();
            }

        protected:

            /**
             * Validates the filled in values
             */
            virtual void CheckInput();

        private:

            /**
             * Initializes the layout
             */
            virtual void Init();

        public slots:

            /**
             * This method is called when the check-box of the movable property
             * is checked or unchecked.
             * This will enable or disable the mass input field
             */
            void MovableCheckboxToggled(bool b_is_checked);

        private:
            // size input fields
            QLineEdit* m_pcEnitySizeXLineEdit;
            QLineEdit* m_pcEnitySizeYLineEdit;
            QLineEdit* m_pcEnitySizeZLineEdit;

            // movable input field
            QCheckBox* m_pcEnityIsMovableCheckBox;

            // mass input field
            QLineEdit* m_pcEnityMassLineEdit;
    };
}

#endif