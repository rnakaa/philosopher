import matplotlib.pyplot as plt
from reportlab.lib.pagesizes import A4
from reportlab.pdfgen import canvas

def create_diagram():
    fig, ax = plt.subplots(figsize=(6, 4))

    # Threadの描画
    plt.text(0.2, 2.5, 'Thread 1', ha='center', va='center')
    plt.text(0.8, 2.5, 'Thread 2', ha='center', va='center')

    # Mutexの描画
    plt.text(0.5, 1.5, 'Mutex', ha='center', va='center')
    plt.plot([0.5], [1.5], marker='o', markersize=10, color='red')

    # アローの描画
    plt.annotate("", xy=(0.5, 1.5), xytext=(0.2, 2.5), arrowprops=dict(arrowstyle="->"))
    plt.annotate("", xy=(0.5, 1.5), xytext=(0.8, 2.5), arrowprops=dict(arrowstyle="->"))

    plt.xlim(0, 1)
    plt.ylim(0, 3)
    plt.axis('off')
    plt.tight_layout()
    plt.savefig('mutex_layout.png', format='png')
    plt.close()

def create_pdf():
    c = canvas.Canvas("mutex_explanation.pdf", pagesize=A4)
    width, height = A4

    # 図の挿入
    c.drawInlineImage("mutex_layout.png", 50, height - 250, width=400, height=200)

    # テキストの挿入
    c.drawString(50, height - 260, "Mutex (Mutual Exclusion) ensures that only one thread at a time accesses a shared resource.")
    c.drawString(50, height - 275, "When one thread acquires the lock (e.g., Thread 1), the other threads must wait until the lock is released.")
    c.drawString(50, height - 290, "This ensures orderly access and prevents conflicts or inconsistencies in the shared resource.")

    c.save()

if __name__ == "__main__":
    create_diagram()
    create_pdf()
    print("PDF created successfully.")


